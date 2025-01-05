/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:30:03 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/05 12:54:24 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* int	parse_line(char **src, int *tab, int size, t_obj *obj)
{
	char	**temp;
	int		j;

	if (!tab || !src)
		return (ft_free_tab((void **)src, line_size(src)), 1);
	temp = src;
	j = 0;
	while (*temp)
	{
		if (j == size || !is_valid_arg(*temp))
			return (ft_free_tab((void **)src, line_size(src)), 1);
		// extract_data(*temp, tab, j, obj);
		tab[j++] = ft_atoi(*temp);
		find_extrem(tab[j - 1], obj);
		temp++;
	}
	ft_free_tab((void **)src, line_size(src));
	if (j != size)
		return (1);
	return (0);
} */

/* void	parse_file(t_mat *mat, char *path, t_obj *obj)
{
	char	**temp;
	char	*line;
	int		fd;
	int		i;

	*mat = (t_mat){NULL, NULL, 0, 0, 0};
	get_matsize(mat, path);
	if (mat->len == 0 || mat->wid == 0)
		ft_perror(0, 0, "The map is empty.");
	mat->matrix = ft_calloc(mat->len + 1, sizeof(int *));
	fd = open(path, O_RDONLY);
	if (fd == -1 || !mat->matrix)
		ft_perror(3, mlx_del(NULL), NULL);
	i = -1;
	while (++i < mat->len)
	{
		line = get_next_line(fd);
		temp = ft_split(line, ' ');
		mat->matrix[i] = ft_calloc(mat->wid + 1, sizeof(int));
		ft_del(line);
		if (!mat->matrix[i] || parse_line(temp, mat->matrix[i], mat->wid, obj))
			ft_perror(4, mlx_del(NULL), NULL);
	}
	close(fd);
} */

int	parse_line(t_obj *obj, char **src, int line)
{
	char	**temp;
	int		j;

	obj->mat.matrix[line] = ft_calloc(obj->mat.wid + 1, sizeof(int));
	obj->mat.color[line] = ft_calloc(obj->mat.wid + 1, sizeof(int));
	if (!obj->mat.matrix[line] || !obj->mat.color[line] || !src)
		return (ft_free_tab((void **)src, line_size(src)), 1);
	temp = src;
	j = 0;
	while (*temp)
	{
		if (j == obj->mat.wid || !is_valid_arg(*temp))
			return (ft_free_tab((void **)src, line_size(src)), 1);
		extract_data(obj, *temp, j, line);
		temp++;
		j++;
	}
	ft_free_tab((void **)src, line_size(src));
	if (j != obj->mat.wid)
		return (1);
	return (0);
}

void	parse_file(t_obj *obj, char *path)
{
	char	**temp;
	char	*line;
	int		fd;
	int		i;

	obj->mat = (t_mat){NULL, NULL, 0, 0, 0};
	get_matsize(&obj->mat, open(path, O_RDONLY));
	if (obj->mat.len == 0 || obj->mat.wid == 0)
		ft_perror(0, 0, "The map is empty.");
	obj->mat.matrix = ft_calloc(obj->mat.len + 1, sizeof(int *));
	obj->mat.color = ft_calloc(obj->mat.len + 1, sizeof(int *));
	fd = open(path, O_RDONLY);
	if (fd == -1 || !obj->mat.matrix || !obj->mat.color)
		ft_perror(3, mlx_del(NULL), NULL);
	i = -1;
	while (++i < obj->mat.len)
	{
		line = get_next_line(fd);
		temp = ft_split(line, ' ');
		ft_del(line);
		if (parse_line(obj, temp, i))
			ft_perror(4, mlx_del(NULL), NULL);
	}
	close(fd);
}
