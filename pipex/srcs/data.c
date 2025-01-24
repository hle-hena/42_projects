/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:06:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/22 16:01:19 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clean_func(t_data *data)
{
	int	i;

	ft_del(data->cmd_path);
	if (data->cmd_arg)
	{
		i = 0;
		while (data->cmd_arg[i])
		{
			ft_del(data->cmd_arg[i]);
			i++;
		}
		ft_del(data->cmd_arg);
	}
	return (0);
}

int	clean_data(t_data *data)
{
	ft_del(data->f_id);
	ft_del(data->p_fd);
	clean_func(data);
	return (0);
}

void	here_doc(t_data *data)
{
	int		p_fd[2];
	pid_t	f_id;
	char	*temp;

	if (pipe(p_fd) == -1)
		ft_perror(1, 0, "The pipe didn't open.");
	f_id = fork();
	if (f_id == -1)
		ft_perror(1, clean_data(data), "A subprocess was not started.");
	if (f_id == 0)
	{
		close(p_fd[0]);
		while (1)
		{
			temp = get_next_line(0);
			if (ft_strncmp(temp, data->av[2], ft_strlen(data->av[2])) == 0
				&& temp[ft_strlen(data->av[2])] == 0)
				return (ft_del(temp), exit(0));
			ft_putstr_fd(temp, p_fd[1]);
			ft_del(temp);
		}
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
}

void	get_fds(t_data *data)
{
	data->fd_in = 0;
	if (data->here_doc)
		here_doc(data);
	else
	{
		data->fd_in = open(data->av[1], O_RDONLY, 0777);
		if (data->fd_in != -1)
			dup2(data->fd_in, 0);
		else
			ft_perror(-1, 0, "First file does not exist.");
	}
	if (data->here_doc == 1)
		data->fd_out = open(data->av[data->ac - 1], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
	else
		data->fd_out = open(data->av[data->ac - 1], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
	if (data->fd_out == -1)
		ft_perror(-1, 0, "Second file does not exist.");
}

void	init_data(t_data *data, int ac, char **av, char **env)
{
	int	i;

	data->ac = ac;
	data->av = av;
	data->env = env;
	data->here_doc = !ft_strncmp("here_doc", av[1], 9);
	data->nb_cmd = ac - 3 - data->here_doc;
	data->cmd_arg = NULL;
	data->cmd_path = NULL;
	get_fds(data);
	data->f_id = ft_calloc(data->nb_cmd, sizeof(int));
	data->p_fd = ft_calloc(data->nb_cmd * 2, sizeof(int));
	if (!data->f_id || !data->p_fd)
		return (ft_perror(1, clean_data(data),
				"Error happened during malloc."));
	i = -1;
	while (++i < data->nb_cmd - 1)
		if (pipe(data->p_fd + 2 * i) == -1)
			return (ft_perror(1, clean_data(data),
					"A pipe failed to open."));
}
