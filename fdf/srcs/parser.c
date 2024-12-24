/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:30:03 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/24 12:10:47 by hle-hena         ###   ########.fr       */
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

void	find_extrem(int val, t_obj *obj)
{
	if (val > obj->max_h)
		obj->max_h = val;
	if (val < obj->min_h)
		obj->min_h = val;
}

int	parse_line(char **src, int *nb, int size, t_obj *obj)
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
		find_extrem(nb[j - 1], obj);
		temp++;
	}
	if (j != size)
		return (ft_free_tab((void **)src, line_size(src)), 1);
	return (0);
}

void	get_matsize(t_mat *mat, char *path)
{
	char	**splited;
	char	*temp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_perror(0, mlx_del(NULL), "Fd is invalid.");
	while (++mat->len)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		if (mat->len == 1)
		{
			splited = ft_split(temp, ' ');
			if (!splited)
				ft_perror(3, mlx_del(NULL), NULL);
			while (splited[mat->wid])
				mat->wid++;
			ft_free_tab((void **)splited, mat->wid);
		}
		free(temp);
	}
	close(fd);
}

void	parse_file(t_mat *mat, char *path, t_obj *obj)
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
		if (!mat->matrix[i] || parse_line(temp, mat->matrix[i], mat->wid, obj))
			ft_perror(4, mlx_del(NULL), NULL);
		ft_free_tab((void **)temp, mat->wid);
	}
	close(fd);
}
