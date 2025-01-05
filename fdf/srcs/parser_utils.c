/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:44:46 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 23:15:11 by hle-hena         ###   ########.fr       */
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

// void	find_extrem(int val, t_obj *obj)
// {
// 	if (val > obj->max_h)
// 		obj->max_h = val;
// 	if (val < obj->min_h)
// 		obj->min_h = val;
// }

void	extract_data(t_obj	*obj, char *data, int x, int y)
{
	obj->mat.matrix[y][x] = ft_atoi(data);
	if (obj->mat.col)
		obj->mat.color[y][x] = ft_max(ft_atoi_base(data, "0123456789ABCDEF"),
			ft_atoi_base(data, "0123456789abcdef"));
	if (obj->mat.matrix[y][x] > obj->max_h)
		obj->max_h = obj->mat.matrix[y][x];
	else if (obj->mat.matrix[y][x] < obj->min_h)
		obj->min_h = obj->mat.matrix[y][x];
}

int	is_valid_arg(t_obj *obj, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
			break;
		if ((i == 0 && (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+'))
			|| (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+'
				&& str[i] != '\n'))
			return (0);
	}
	if (!str[i])
		return (1);
	obj->mat.col = 1;
	if (str[i + 1] != '0' && str[i + 2] != 'x')
		return (0);
	i += 2;
	while (str[++i])
	{
		if (!ft_strchr("0123456789ABCDEF", str[i])
			&& !ft_strchr("abcdef", str[i]) && str[i] != '\n')
			return (0);
	}
	return (1);
}

void	get_matsize(t_mat *mat, char *path)
{
	char	**splited;
	char	*temp;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_perror(0, mlx_del(NULL), "Fd is invalid.");
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		if (mat->len == 0)
		{
			splited = ft_split(temp, ' ');
			if (!splited)
				ft_perror(3, mlx_del(NULL), NULL);
			while (splited[mat->wid])
				mat->wid++;
			ft_free_tab((void **)splited, mat->wid);
		}
		free(temp);
		mat->len++;
	}
	close(fd);
}
