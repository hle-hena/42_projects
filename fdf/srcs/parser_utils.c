/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:44:46 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/07 16:42:18 by hle-hena         ###   ########.fr       */
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

void	extract_data(t_obj	*obj, char *data, int x, int y)
{
	char	*src;

	obj->mat.matrix[y][x] = ft_atoi(data);
	if (obj->mat.col)
	{
		src = ft_strchr(data, 'x');
		if (!src)
			obj->mat.color[y][x] = 0xFFFFFF;
		else
			obj->mat.color[y][x] = ft_atoi_base(ft_tolower(src + 1),
					"0123456789abcdef", 16);
	}
	if (obj->mat.matrix[y][x] > obj->max_h)
		obj->max_h = obj->mat.matrix[y][x];
	else if (obj->mat.matrix[y][x] < obj->min_h)
		obj->min_h = obj->mat.matrix[y][x];
}

int	is_valid_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != ' ' && str[i])
	{
		if (str[i] == ',')
			break ;
		if ((i == 0 && (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+'))
			|| (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+'
				&& str[i] != '\n'))
			return (-1);
	}
	if (str[i] == ' ' || !str[i])
		return (i - !str[i]);
	if (str[i + 1] != '0' && str[i + 2] != 'x')
		return (-1);
	i += 2;
	while (str[++i] != ' ' && str[i])
	{
		if (!ft_strchr("0123456789ABCDEF", str[i])
			&& !ft_strchr("abcdef", str[i]) && str[i] != '\n')
			return (-1);
	}
	return (i - !str[i]);
}

void	get_matsize(t_mat *mat, int fd)
{
	char	**splited;
	char	*temp;

	if (fd == -1)
		ft_perror(0, mlx_del(NULL), "Fd is invalid.");
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		if (ft_strchr(temp, ','))
			mat->col = 1;
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
