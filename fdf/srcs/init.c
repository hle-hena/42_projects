/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/11 12:26:39 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_line(char **src, int *nb, int size)
{
	char	**temp;
	int		i;
	int		j;

	if (!nb)
		return (1);
	temp = src;
	j = 0;
	while (*temp)
	{
		if (j == size)
			return (1);
		i = -1;
		while ((*temp)[++i])
		{
			if (!ft_isdigit((*temp)[i]) && (*temp)[i] != '-' && (*temp)[i] != '+'
					&& (*temp)[i] != '\n')
				exit(0); ///////// probably a return and not an exit
		}
		nb[j] = ft_atoi(*temp);
		temp++;
		j++;
	}
	return (0);
}

void	get_matsize(t_mat *matrix, char *path)
{
	char	**splited;
	char	*temp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(1);
	while (++matrix->len)
	{
		temp = get_next_line(fd);
		if (!temp)
			break;
		if (matrix->len == 1)
		{
			splited = ft_split(temp, ' ');
			if (!splited)
				exit(1);
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
	mat->matrix = ft_calloc(mat->len, sizeof(int *));
	fd = open(path, O_RDONLY);
	if (fd == -1 || !mat->matrix)
		exit(1);
	i = -1;
	while (++i < mat->len - 1)
	{
		line = get_next_line(fd);
		temp = ft_split(line, ' ');
		mat->matrix[i] = ft_calloc(mat->wid + 1, sizeof(int));
		if (!mat->matrix[i] || get_line(temp, mat->matrix[i], mat->wid))
			exit(1);
		ft_free_tab((void **)temp, mat->wid);
		ft_del(line);
	}
	close(fd);
}

void	init_data(t_data *data, char *path)
{
	init_matrix(&data->matrix, path);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
			printf("%d - ", data->matrix.matrix[i][j]);
		printf("%d\n", data->matrix.matrix[i][2]);
	}
	data->display = (t_disp){0, 0, 1};
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1000, 1000, "Hello world!");
}