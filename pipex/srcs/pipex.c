/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:58:09 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/21 17:20:13 by hle-hena         ###   ########.fr       */
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
		return (ft_perror(3, 0, "Path not found."), NULL);
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
	if (!av[0])
		return (ft_free_tab((void **)av, count_words(args, ' ')),
			ft_perror(127, 0, "A function given was invalid."));
	path = get_path(av[0], env);
	if (!path)
		return (ft_free_tab((void **)av, count_words(args, ' ')),
			ft_perror(127, 0, "A function given was invalid."));
	if (execve(path, av, env) == -1)
	{
		ft_free_tab((void **)av, count_words(args, ' '));
		ft_del(path);
		ft_perror(127, 0, "An error occured during the execution of \
the command.");
	}
}

void	do_func(char *args, char **env)
{
	int		p_fd[2];
	pid_t	f_id;

	if (pipe(p_fd) == -1)
		ft_perror(1, 0, "The pipe didn't open.");
	f_id = fork();
	if (f_id == -1)
		ft_perror(1, 0, "A subprocess was not started.");
	if (f_id == 0)
	{
		close(p_fd[0]);
		dup2(p_fd[1], 1);
		close(p_fd[1]);
		exec_func(args, env);
		exit(EXIT_FAILURE);
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	if (!ft_strncmp(args, "sleep", 5))
		waitpid(f_id, NULL, 0);
}

void	here_doc(char *limiter)
{
	int		p_fd[2];
	pid_t	f_id;
	char	*temp;

	if (pipe(p_fd) == -1)
		ft_perror(1, 0, "The pipe didn't open.");
	f_id = fork();
	if (f_id == -1)
		ft_perror(1, 0, "A subprocess was not started.");
	if (f_id == 0)
	{
		close(p_fd[0]);
		while (1)
		{
			temp = get_next_line(0);
			if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
				&& temp[ft_strlen(limiter)] == '\n')
				return (ft_del(temp), exit(0));
			ft_putstr_fd(temp, p_fd[1]);
			ft_del(temp);
		}
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
}

//p_fd[0] -> R
//p_fd[1] -> W
int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd;

	if (ac < 5 + (ft_strncmp("here_doc", av[1 * (ac > 5)], 9) == 0))
		return (ft_perror(1, 0, "Not enough arguments."), 0);
	i = 1 + (ft_strncmp("here_doc", av[1], 9) == 0);
	if (i == 1)
	{
		fd = open(av[i], O_RDONLY, 0777);
		if (fd == -1)
			ft_perror(-1, 0, "First file does not exist.");
		fd = ft_tern_int(fd == -1, 1, fd);
		dup2(fd, 0);
	}
	else
		here_doc(av[2]);
	while (++i < ac - 2)
		do_func(av[i], env);
	if (ft_strncmp("here_doc", av[1], 9) != 0)
		close(fd);
	fd = open(av[ac - 1], O_CREAT | ft_tern_int(ft_strncmp("here_doc", av[1], 9)
				== 0, O_APPEND, O_TRUNC) | O_WRONLY, 0777);
	if (fd == -1)
		ft_perror(1, 0, "Second file does not exist.");
	return (dup2(fd, 1), exec_func(av[i], env), 0);
}
