/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/10 16:19:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_line(char **src, int *int)
{
	char	**temp;
	int		i;

	temp = src;
	while (*temp)
	{
		i = -1;
		while (*temp[++i])
		{
			if (!ft_isdigit(*temp[i]) && *temp[i] != '-' && *temp[i] != '+')
				exit(0);
		}
	}
}

int	get_matsize(t_mat *matrix, char *path)
{
	char	**splited;
	int		fd;
	int		i;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(0);
	while (++matrix->len)
	{
		temp = get_next_line(fd);
		if (!temp)
			break;
		if (matrix->len == 1)
		{
			splited = ft_split(temp, ' ');
			if (!splited)
				return (1) ///////////////////should be an exit ?
			matrix->width = sizeof(splited) / sizeof(char *);
			i = -1;
			while (splited[++i])
				free(splited[i]);
			free(splited);
		}
		free(temp);
	}
	close(fd);
}

void	init_matrix(t_mat *matrix, char *path)
{
	char	**temp;
	int		i;

	*matrix = (t_mat){NULL, 0, 0};
	get_matsize(matrix, path);
	matrix->matrix = ft_calloc(matrix.len, sizeof(int *));
	fd = open(path, O_RDONLY);
	if (fd == -1 || !matrix->matrix)
		exit(0);
	i = 0;
	while (++i)
	{
		temp = ft_split(get_next_line(fd), ' ');
		matrix->matrix[i - 1] = ft_calloc(matrix.width + 1, sizeof(int));
		if (!matrix->matrix[i - 1] || !temp)
			exit(0);
		get_line(temp, )
	}
	close(fd);
}

void	init_data(t_data *data, char *path)
{
	char	**temp;
	int		fd;

	init_matrix(&data->matrix, path);
	data->display = (t_disp){0, 0, 1};
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1000, 1000, "Hello world!");
}