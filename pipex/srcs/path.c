/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:29:08 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/22 14:52:30 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_strs(char *str, char **strs)
{
	int	i;

	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	if (strs != NULL)
	{
		i = 0;
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

char	*get_path_line(t_data *data)
{
	int		i;
	char	*paths;

	i = 0;
	paths = ft_strnstr(data->env[i], "PATH=", 5);
	while (!paths && data->env[++i])
		paths = ft_strnstr(data->env[i], "PATH=", 5);
	if (!paths)
		return (ft_perror(3, clean_data(data), "Path not found."), NULL);
	return (paths);
}

char	*get_path(t_data *data)
{
	char	**tries;
	char	*paths;
	char	*path;
	char	*temp;
	int		i;

	if (!data->cmd_arg)
		return (ft_perror(1, clean_data(data), "Error happened during split."),
			NULL);
	if (!data->cmd_arg[0])
		return (ft_perror(-1, 0, "Empty argument as function."), NULL);
	i = -1;
	paths = get_path_line(data);
	tries = ft_split(paths, ':');
	while (tries && tries[++i])
	{
		temp = ft_strjoin(tries[i], "/");
		path = ft_strjoin(temp, data->cmd_arg[0]);
		ft_del(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_tab((void **)tries, count_words(paths, ':')), path);
		ft_del(path);
	}
	ft_free_tab((void **)tries, count_words(paths, ':'));
	return (ft_perror(-1, 0, "Command not found."), NULL);
}
