/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/11 18:38:17 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	line_size(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	get_line(char **src, int *nb, int size)
{
	char	**temp;
	int		i;
	int		j;

	if (!nb || !src)
		return (ft_free_tab((void **)src, line_size(src)), 1);
	temp = src;
	j = 0;
	while (*temp)
	{
		if (j == size)
			return (ft_free_tab((void **)src, line_size(src)), 1);
		i = -1;
		while ((*temp)[++i])
		{
			if (!ft_isdigit((*temp)[i]) && (*temp)[i] != '-'
					&& (*temp)[i] != '+' && (*temp)[i] != '\n')
				return (ft_free_tab((void **)src, line_size(src)), 1);
		}
		nb[j++] = ft_atoi(*temp);
		temp++;
	}
	if (j != size)
		return (ft_free_tab((void **)src, line_size(src)), 1);
	return (0);
}

void	get_matsize(t_mat *matrix, char *path)
{
	char	**splited;
	char	*temp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_perror(0, mlx_del(NULL), "Fd is invalid.");
	while (++matrix->len)
	{
		temp = get_next_line(fd);
		if (!temp)
			break;
		if (matrix->len == 1)
		{
			splited = ft_split(temp, ' ');
			if (!splited)
				ft_perror(3, mlx_del(NULL), NULL);
			while (splited[matrix->wid])
				matrix->wid++;
			ft_free_tab((void **)splited, matrix->wid);
		}
		free(temp);
	}
	close(fd);
}

void	init_matrix(t_mat *mat, char *path)
{
	char	**temp;
	char	*line;
	int		fd;
	int		i;

	*mat = (t_mat){NULL, 0, 0};
	get_matsize(mat, path);
	if (mat->len == 0 || mat->wid == 0)
		ft_perror(0, 0, "The map is empty.");
	mat->matrix = ft_calloc(mat->len, sizeof(int *));
	fd = open(path, O_RDONLY);
	if (fd == -1 || !mat->matrix)
		ft_perror(3, mlx_del(NULL), NULL);
	i = -1;
	while (++i < mat->len - 1)
	{
		line = get_next_line(fd);
		temp = ft_split(line, ' ');
		mat->matrix[i] = ft_calloc(mat->wid + 1, sizeof(int));
		ft_del(line);
		if (!mat->matrix[i] || get_line(temp, mat->matrix[i], mat->wid))
			ft_perror(4, mlx_del(NULL), NULL);
		ft_free_tab((void **)temp, mat->wid);
	}
	close(fd);
}

void	init_data(t_data *data, char *path)
{
	init_matrix(&data->matrix, path);
	for (int i = 0; i < data->matrix.len - 1; i++)
	{
		for (int j = 0; j < data->matrix.wid - 1; j++)
			printf("%d - ", data->matrix.matrix[i][j]);
		printf("%d\n", data->matrix.matrix[i][data->matrix.wid - 1]);
	}
	data->display = (t_disp){0, 0, 1};
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1000, 1000, "Hello world!");
}