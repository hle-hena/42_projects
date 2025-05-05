/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:36:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/05 16:34:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_redirect(char *line, int *forward, t_cmd *cmd, char **temp)
{
	char	*str;
	int		err;
	int		sep;
	t_op	*open;

	err = 0;
	str = tokenize(line, forward, &err, &sep);
	open = ft_calloc(1, sizeof(t_op));
	if (!open)
		ft_perror(1, "Internal error: malloc.", 0);
	if (!str || err || ft_strchr("><|&()", str[0]))
	{
		ft_del((void **)temp);
		return (*temp = str);
	}
	if (ft_strncmp(">", *temp, 2))
		open->mode = 0;
	else if (ft_strncmp(">>", *temp, 3))
		open->mode = 1;
	else if (ft_strncmp("<", *temp, 2))
		open->mode = 2;
	else if (ft_strncmp("<<", *temp, 3))
		open->mode = 3;
	else if (ft_strncmp("<>", *temp, 3))
		open->mode = 4;
	open->str = str;
	return (add_link(&cmd->open, open), NULL);
}

void	clear_open(t_list **open)
{
	t_list	*temp;

	while (*open)
	{
		temp = (*open)->next;
		ft_del((void **)&((t_op *)(*open)->content)->str);
		ft_del(&(*open)->content);
		ft_del((void **)open);
		*open = temp;
	}
	*open = 0;
}

void	clear_cmd(t_cmd *cmd, t_list *args, char *current)
{
	int	i;

	if (cmd)
	{
		clear_open(&cmd->open);
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

	if (!args && !cmd->open)
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
	int		separator;
	char	*current;

	i = 0;
	separator = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	args = NULL;
	if (!line[0])
		return (*sep = NULL, build_cmd(cmd, NULL));
	if (ft_strchr("()", line[0]))
		return (ft_del((void **)&cmd), get_subshell(line, forward, sep));
	while (line[i])
	{
		current = tokenize(&line[i], &i, &err, &separator);
		if (err)
			return (*forward += i, clear_cmd(cmd, args, current), *sep = NULL, NULL);
		if (!current)
			continue ;
		if (separator)
			return (*forward += i, *sep = current,  (cmd, args));
		else if (current[0] == '>' || current[0] == '<')
		{
			if (get_redirect(&line[i], &i, cmd, &current))
				return (*forward += i, *sep = current, clear_cmd(cmd, args, NULL), NULL);
		}
		else
			add_link(&args, current);
	}
	return (*forward += i, *sep = NULL, build_cmd(cmd, args));
}

// t_cmd	*get_next_cmd(char *line, int *forward, char **sep, int err)
// {
// 	t_cmd	*cmd;
// 	t_list	*args;
// 	int		i;
// 	int		redirect;
// 	char	*current;

// 	i = 0;
// 	cmd = malloc(sizeof(t_cmd));
// 	*cmd = (t_cmd){NULL, NULL, 0};
// 	args = NULL;
// 	if (!line[0])
// 		return (*sep = NULL, build_cmd(cmd, NULL));
// 	if (ft_strchr("()", line[0]))
// 		return (ft_del((void **)&cmd), get_subshell(line, forward, sep));
// }

void	clear_pipeline(t_list *cmd)
{
	int		i;
	t_list	*next;

	while (cmd)
	{
		clear_open(&((t_cmd *)cmd->content)->open);
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
	sep_local = NULL;
	while (line[i])
	{
		temp = get_next_cmd(&line[i], &i, &sep_local, 0);
		if (!temp)
			return (*sep = sep_local, *forward += i, clear_pipeline(cmd), NULL);
		add_link(&cmd, temp);
		if (sep_local && !line[i])
			return (*sep = sep_local, *forward += i, clear_pipeline(cmd), NULL);
		if (ft_strncmp(sep_local, "&", 2) == 0)
			return (*sep = sep_local, *forward += i, clear_pipeline(cmd), NULL);
		if ((ft_strncmp(sep_local, "||", 3) == 0)
			|| ((ft_strncmp(sep_local, "&&", 3) == 0)))
			return (*sep = sep_local, *forward += i, cmd);
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
