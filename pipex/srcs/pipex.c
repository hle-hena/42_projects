/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:15:20 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/22 14:51:40 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_data *data)
{
	int	i;

	if (data->fd_out != -1)
		close(data->fd_out);
	i = -1;
	while (++i < (data->nb_cmd - 1) * 2)
		close(data->p_fd[i]);
}

int	parent(t_data *data)
{
	pid_t	wpid;
	int		child;
	int		status;
	int		exit_code;

	close_fds(data);
	child = data->nb_cmd;
	exit_code = 1;
	while (--child >= 0)
	{
		wpid = waitpid(data->f_id[child], &status, 0);
		if (wpid == data->f_id[data->nb_cmd - 1])
			if ((child == (data->nb_cmd - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
	}
	ft_del(data->p_fd);
	ft_del(data->f_id);
	if (data->fd_out == -1)
		exit_code = 1;
	return (exit_code);
}

void	set_in_out(t_data *data, int in, int out)
{
	if (dup2(in, 0) == -1)
		return (clean_data(data), exit(0));
	if (dup2(out, 1) == -1)
		return (clean_data(data), exit(0));
}

void	exec_child(t_data *data, int child)
{
	if (child == 0 && data->fd_in == -1)
		return (clean_data(data), exit(0));
	if (child == 0)
		set_in_out(data, 0, data->p_fd[1]);
	else if (child == data->nb_cmd - 1)
		set_in_out(data, data->p_fd[child * 2 - 2], data->fd_out);
	else
		set_in_out(data, data->p_fd[child * 2 - 2], data->p_fd[child * 2 + 1]);
	close_fds(data);
	if (!data->cmd_path)
		return (clean_data(data), exit(127));
	if (execve(data->cmd_path, data->cmd_arg, data->env) == -1)
		ft_perror(127, clean_data(data), "An error occured during the execution of \
the command.");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		child;

	if (ac < 5 + (ft_strncmp("here_doc", av[1 * (ac > 5)], 9) == 0))
		return (ft_perror(1, 0, "Not enough arguments."), 0);
	init_data(&data, ac, av, env);
	child = -1;
	while (++child < data.nb_cmd)
	{
		data.cmd_arg = ft_split(data.av[child + 2 + data.here_doc], ' ');
		data.cmd_path = get_path(&data);
		data.f_id[child] = fork();
		if (data.f_id[child] == -1)
			ft_perror(1, 0, "A subprocess was not started.");
		if (data.f_id[child] == 0)
			exec_child(&data, child);
		clean_func(&data);
	}
	return (parent(&data));
}
