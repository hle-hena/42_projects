/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:58:09 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/17 19:40:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char *func_name, char **env)
{
	char	**tries;
	char	*paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	paths = ft_strnstr(env[i], "PATH=", 5);
	while (!paths && env[++i])
		paths = ft_strnstr(env[i], "PATH=", 5);
	if (!paths)
		return (ft_perror(0, 0, "Path not found."), NULL);
	i = -1;
	tries = ft_split(paths, ':');
	while (tries && tries[++i])
	{
		temp = ft_strjoin(tries[i], "/");
		path = ft_strjoin(temp, func_name);
		ft_del(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	return (ft_free_tab((void **)tries, count_words(paths, ':')), NULL);
}

void	exec_func(char *args, char **env)
{
	char	**av;
	char	*path;

	av = ft_split(args, ' ');
	path = get_path(av[0], env);
	if (!path)
		return (ft_free_tab((void **)av, count_words(args, ' ')), ft_perror(0, 0,
				"A function given was invalid.\n"));
	if (execve(path, av, env) == -1)
	{
		ft_free_tab((void **)av, count_words(args, ' '));
		ft_del(path);
		ft_perror(0, 0, "An error occured during the execution of \
the command.");
	}
}

void	do_func(char *args, char **env)
{
	int		p_fd[2];
	pid_t	f_id;

	if (pipe(p_fd) == -1)
		ft_perror(0, 0, "The pipe didn't open.");
	f_id = fork();
	if (f_id == -1)
		ft_perror(0, 0, "A subprocess was not started.");
	if (f_id == 0)
	{
		dup2(p_fd[1], 1);
		close(p_fd[0]);
		exec_func(args, env);
	}
	dup2(p_fd[0], 0);
	close(p_fd[1]);
}

//p_fd[0] -> R
//p_fd[1] -> W
int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd;

	if (ac < 5)
		ft_perror(0, 0, "Not enough arguments.");
	i = 1;
	fd = open(av[i], O_CREAT | O_RDONLY, 0777);
	if (fd == -1)
		return (ft_perror(0, 0, "One of the file name is incorect."), 0);
	dup2(fd, 0);
	while (++i < ac - 2)
		do_func(av[i], env);
	close(fd);
	fd = open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		return (ft_perror(0, 0, "One of the file name is incorect."), 0);
	dup2(fd, 1);
	exec_func(av[i], env);
	return (0);
}
