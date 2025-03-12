/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:28:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/11 20:11:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_sep(char *line, int *forward)
{
	char	*res;
	int		i;

	i = 1;
	if ((line[0] == line[1]) || (line[0] == '<' && line[0] == '>'))
	{
		res = ft_substr(line, 0, 2);
		i = 2;
	}
	else
		res = ft_substr(line, 0, 1);
	while (ft_isspace(line[i]))
		i++;
	*forward += i;
	return (res);
}

int	get_change(char *line, int *forward, t_list **head)
{
	t_list	*temp;
	int		rv;

	rv = 0;
	temp = NULL;
	if (line[0] == 39 || line[0] == 34)
	{
		temp = get_quote(&line[1], line[0], forward);
		if (!temp)
			rv = 1;
	}
	else if (line[0] == '$')
		temp = get_var_new(&line[0], forward);
	if (rv)
		return (ft_lstclear(&temp, ft_del), rv);
	if (!rv && !temp)
		return (rv);
	else
		return (ft_lstadd_back(head, temp), rv);
}

char	*get_next_block(char *line, int *forward, int *err)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return (*forward += i, *err = 0, NULL);
	if (ft_strchr("()", line[i]))
	{
		head = get_parenthesis(&line[i], &i, err);
		*forward += i;
		return (ft_lstjoin(head));
	}
	if (ft_strchr("><|&", line[i]))
		return (*err = 0, get_sep(line, forward));
	while (line[i] && !ft_isspace(line[i]))
	{
		if (get_change(&line[i], &i, &head))
			return (*forward += i, *err = 1, ft_lstclear(&head, ft_del), NULL);
		if ((ft_strchr("><|&() ", line[i])))
			break ;
		add_link(&head, ft_strdup(&line[i]));
		i++;
	}
	while (ft_isspace(line[i]))
		i++;
	*forward += i;
	return (*err = 0, ft_lstjoin(head));
}

t_cmd	*get_subblock(char *line, int *forward, char **sep)
{
	t_cmd	*cmd;
	char	**args;
	char	*block;
	int		err;
	int		i;

	block = get_next_block(line, &i, &err);
	*forward += i;
	if (err)
		return (NULL);
	args = malloc(2 * sizeof(char *));
	args[0] = block;
	args[1] = NULL;
	block = get_next_block(&line[i], &i, &err);
	*forward += i;
	if (err)
		return (ft_del(args[0]), ft_del(args), NULL);
	*sep = block;
	cmd = malloc(1 * sizeof(t_cmd));
	cmd[0] = (t_cmd){NULL, NULL, args, NULL, 0, NULL};
	return (cmd);
}

//If I want to have the real way this works, I shouldnt do it like that for the opening of the files.
int	get_redirect(char *line, int *forward, t_cmd *cmd, char **redirect)
{
	char	*file_name;
	int		err;

	err = 0;
	file_name = get_next_block(line, forward, &err);
	if (file_name || err || !line[0])
	{
		if (!line[0] || ft_strchr("><|&()", file_name[0]) || err)
		{
			ft_del(*redirect);
			*redirect = file_name;
			return (0);
		}
	}
	if ((*redirect)[0] == '>')
	{
		ft_del(cmd->out);
		cmd->out = file_name;
		cmd->append = ((*redirect)[1] == '>');
		ft_del(*redirect);
		if (!file_name)
			return (1);
		return (close(open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)), 1);
	}
	if ((*redirect)[1])
	{
		ft_del(cmd->here_doc);
		return (ft_del(*redirect), cmd->here_doc = file_name, 1);
	}
	ft_del(cmd->in);
	return (ft_del(*redirect), cmd->in = file_name, 1);
}

void	clear_cmd(t_cmd *cmd, t_list *args, char *current)
{
	ft_del(cmd->here_doc);
	ft_del(cmd->in);
	ft_del(cmd->out);
	ft_lstclear(&args, ft_del);
	ft_del(current);
}

t_cmd	*build_cmd(t_cmd *cmd, t_list *args)
{
	t_list	*next;
	char	**av;
	int		i;

	if (!args && !cmd->here_doc && !cmd->in && !cmd->out)
		return (ft_del(cmd), NULL);
	av = malloc((ft_lstsize(args) + 1) * sizeof(char *));
	i = 0;
	while (args)
	{
		av[i++] = args->content;
		next = args->next;
		ft_del(args);
		args = next;
	}
	av[i] = NULL;
	cmd->args = av;
	return (cmd);
}

t_cmd	*get_next_cmd(char *line, int *forward, char **sep)
{
	t_cmd	*cmd;
	t_list	*args;
	int		i;
	int		err;
	char	*current;

	i = 0;
	cmd = malloc(sizeof(t_cmd) * 1);
	*cmd = (t_cmd){NULL, NULL, NULL, NULL, 0, NULL};
	args = NULL;
	if (ft_strchr("()", line[0]))
		return (get_subblock(line, forward, sep));
	while (line[i])
	{
		current = get_next_block(&line[i], &i, &err);
		if (err)
			return (*forward += i, clear_cmd(cmd, args, current), *sep = current, NULL);
		if (current != NULL)
		{
			if ((ft_strncmp(current, "||", 3) == 0)
				|| ((ft_strncmp(current, "&&", 3) == 0))
				|| (ft_strncmp(current, "|", 2) == 0))
				return (*forward += i, *sep = current, build_cmd(cmd, args));
			else if (ft_strchr("()", current[0]))
				return (*forward += i, *sep = current, clear_cmd(cmd, args, current), NULL);
			else if (ft_strchr("><", current[0]))
			{
				if (!get_redirect(&line[i], &i, cmd, &current))
					return (*forward += i, *sep = current, clear_cmd(cmd, args, NULL), NULL);
			}
			else
				add_link(&args, current);
		}
	}
	return (*forward += i, *sep = NULL, build_cmd(cmd, args));
}

// t_cmd	*create_pipeline(t_list *cmd)
// {
	
// }

// t_cmd	*get_next_pipeline(char *line, int *forward, char *sep)
// {
// 	t_list	*cmd;
// 	t_cmd	*temp;
// 	int		i;
// 	char	*sep;

// 	i = 0;
// 	cmd = NULL;
// 	while (line[i])
// 	{
// 		temp = get_next_cmd(&line[i], &i, &sep);
// 		if (!temp)
// 			return (NULL);
// 		add_link(&cmd, temp);
// 		if ((ft_strncmp(sep, "||", 3) == 0)
// 			|| ((ft_strncmp(sep, "&&", 3) == 0)))
// 			return (create_pipeline(cmd));
// 		// if (ft_strncmp(sep, "&", 2) == 0)
// 		// 	;//Print smthing like invalid sep.
// 	}
// 	return (sep = NULL, cmd);
// }

// t_list	*get_cmds(char *line)
// {
// 	t_list	*blocks;
// 	int		start;

// 	start = 0;
// }
