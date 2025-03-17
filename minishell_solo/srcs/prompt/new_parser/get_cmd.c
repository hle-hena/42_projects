/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:28:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/15 14:49:01 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_sep(char *line, int *forward)
{
	char	*res;
	int		i;

	i = 1;
	if ((line[0] == line[1]) || (line[0] == '<' && line[1] == '>'))
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
	else if (line[0] == '~' && (!line[1] || line[1] == '/'))
		temp = get_tilde(forward);
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
	while (ft_isspace(line[i]) && line[i])
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
	while (ft_isspace(line[i]) && line[i])
		i++;
	*forward += i;
	return (*err = 0, ft_lstjoin(head));
}

t_cmd	*get_subblock(char *line, int *forward, char **sep)
{
	t_cmd	*cmd;
	char	*block;
	int		err;
	int		i;

	i = 0;
	block = get_next_block(line, &i, &err);
	if (err)
		return (*forward += i, *sep = NULL, NULL);
	cmd = malloc(1 * sizeof(t_cmd));
	if (!cmd)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."), clean_data());
	*cmd = (t_cmd){NULL, NULL, NULL, NULL, 0, 1};
	cmd->args = malloc(2 * sizeof(char *));
	if (!cmd->args)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."), clean_data());
	cmd->args[0] = block;
	cmd->args[1] = NULL;
	if (!line[i])
		return (*forward += i, *sep = NULL, cmd);
	block = get_next_block(&line[i], &i, &err);
	*forward += i;
	if (err)
		return (clear_cmd(cmd, NULL, NULL), *sep = NULL, NULL);
	return (*sep = block, cmd);
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
		if (!line[0] || ft_strchr("><|&()", line[0]) || err)
		{
			ft_del((void **)redirect);
			*redirect = file_name;
			return (0);
		}
	}
	if ((*redirect)[0] == '<' && (*redirect)[1] == '>')
	{
		if (file_name)
			close(open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644));
		ft_del((void **)&cmd->out);
		ft_del((void **)&cmd->in);
		ft_del((void **)redirect);
		cmd->out = file_name;
		cmd->in = file_name;
		return (1);
	}
	if ((*redirect)[0] == '>')
	{
		ft_del((void **)&cmd->out);
		cmd->out = file_name;
		cmd->append = ((*redirect)[1] == '>');
		ft_del((void **)redirect);
		if (!file_name)
			return (1);
		return (close(open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)), 1);
	}
	if ((*redirect)[1])
	{
		ft_del((void **)&cmd->here_doc);
		return (ft_del((void **)redirect), cmd->here_doc = file_name, 1);
	}
	ft_del((void **)&cmd->in);
	return (ft_del((void **)redirect), cmd->in = file_name, 1);
}

void	clear_cmd(t_cmd *cmd, t_list *args, char *current)
{
	int	i;

	if (cmd)
	{
		ft_del((void **)&cmd->here_doc);
		ft_del((void **)&cmd->in);
		ft_del((void **)&cmd->out);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
				ft_del((void **)&cmd->args[i++]);
			ft_del((void **)&cmd->args);
		}
		ft_del((void **)&cmd);
	}
	if (args)
		ft_lstclear(&args, ft_del);
	ft_del((void **)&current);
}

t_cmd	*build_cmd(t_cmd *cmd, t_list *args)
{
	t_list	*next;
	char	**av;
	int		i;

	if (!args && !cmd->here_doc && !cmd->in && !cmd->out)
		return (ft_del((void **)&cmd), NULL);
	av = malloc((ft_lstsize(args) + 1) * sizeof(char *));
	i = 0;
	while (args)
	{
		av[i++] = args->content;
		next = args->next;
		ft_del((void **)&args);
		args = next;
	}
	av[i] = NULL;
	cmd->args = av;
	return (cmd);
}

t_cmd	*get_next_cmd(char *line, int *forward, char **sep, int err)
{
	t_cmd	*cmd;
	t_list	*args;
	int		i;
	int		redirect;
	char	*current;

	i = 0;
	cmd = malloc(sizeof(t_cmd) * 1);
	*cmd = (t_cmd){NULL, NULL, NULL, NULL, 0, 0};
	args = NULL;
	if (!line[0])
		return (*sep = NULL, build_cmd(cmd, NULL));
	if (ft_strchr("()", line[0]))
		return (ft_del((void **)&cmd), get_subblock(line, forward, sep));
	while (line[i])
	{
		redirect = (line[i] == '>' || line[i] == '<');
		current = get_next_block(&line[i], &i, &err);
		if (err)
			return (*forward += i, clear_cmd(cmd, args, current), *sep = current, NULL);
		if (current != NULL)
		{
			if ((ft_strncmp(current, "||", 3) == 0)
				|| ((ft_strncmp(current, "&&", 3) == 0))
				|| (ft_strncmp(current, "|", 2) == 0)
				|| (ft_strncmp(current, "&", 2) == 0))
				return (*forward += i, *sep = current, build_cmd(cmd, args));
			else if (current[0] == '(' || current[0] == ')')
				return (*forward += i, *sep = current, clear_cmd(cmd, args, NULL), NULL);
			else if ((current[0] == '<' || current[0] == '>') && redirect)
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

void	clear_pipeline(t_list *cmd)
{
	int		i;
	t_list	*next;

	while (cmd)
	{
		ft_del((void **)&((t_cmd *)cmd->content)->here_doc);
		ft_del((void **)&((t_cmd *)cmd->content)->in);
		ft_del((void **)&((t_cmd *)cmd->content)->out);
		if (((t_cmd *)cmd->content)->args)
		{
			i = 0;
			while (((t_cmd *)cmd->content)->args[i])
				ft_del((void **)&((t_cmd *)cmd->content)->args[i++]);
			ft_del((void **)&(((t_cmd *)cmd->content)->args));
		}
		ft_del((void **)&cmd->content);
		next = cmd->next;
		ft_del((void **)&cmd);
		cmd = next;
	}
}

t_list	*get_next_pipeline(char *line, int *forward, char **sep)
{
	t_list	*cmd;
	t_cmd	*temp;
	int		i;
	char	*sep_local;

	i = 0;
	cmd = NULL;
	if (!line[i])
	{
		temp = malloc(sizeof(t_cmd) * 1);
		*temp = (t_cmd){NULL, NULL, NULL, NULL, 0, 0};
		add_link(&cmd, temp);
		return (*sep = NULL, cmd);
	}
	while (line[i])
	{
		temp = get_next_cmd(&line[i], &i, &sep_local, 0);
		if (!temp)
			return (*sep = sep_local, *forward += i, clear_pipeline(cmd), NULL);
		add_link(&cmd, temp);
		if (sep_local && !line[i])
			return (*sep = sep_local, *forward += i, clear_pipeline(cmd), NULL);
		if ((ft_strncmp(sep_local, "||", 3) == 0)
			|| ((ft_strncmp(sep_local, "&&", 3) == 0)))
			return (*sep = sep_local, *forward += i, cmd);
		if (ft_strncmp(sep_local, "&", 2) == 0)
			return (*sep = sep_local, *forward += i, clear_pipeline(cmd), NULL);
		ft_del((void **)&sep_local);
	}
	return (*sep = NULL, *forward += i, cmd);
}

void	clear_blocks(t_list *cmds)
{
	t_list	*next;

	while (cmds)
	{
		clear_pipeline((t_list *)cmds->content);
		next = cmds->next;
		ft_del((void **)&cmds);
		cmds = next;
		if (cmds)
		{
			ft_del((void **)&cmds->content);
			next = cmds->next;
			ft_del((void **)&cmds);
			cmds = next;
		}
	}
}

t_list	*get_cmds(char *line, char **err_token)
{
	t_list	*blocks;
	t_list	*temp;
	char	*sep;
	int		i;

	i = 0;
	blocks = NULL;
	while (line[i])
	{
		temp = get_next_pipeline(&line[i], &i, &sep);
		if (!temp || (sep && !line[i]))
			return (*err_token = sep, clear_pipeline(temp),
				clear_blocks(blocks), NULL);
		add_link(&blocks, temp);
		if (!sep)
			return (*err_token = NULL, blocks);
		add_link(&blocks, sep);
	}
	return (*err_token = NULL, blocks);
}
