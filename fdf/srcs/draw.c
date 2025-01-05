/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/05 11:08:31 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, t_vec start, t_vec end, int col)
{
	t_line	line;

	if (!calc_point(data, &line, &start, &end))
		return ;
	if (col == 0)
	{
		line.start.col = (t_col){0, 0, 0};
		line.end.col = (t_col){0, 0, 0};
	}
	else
		set_color(data, &line, start, end);
	if (!move_point(data, &line.start, &line.end))
		return ;
	if (line.start.x == line.end.x && line.start.y == line.end.y
		&& line.start.z == line.end.z)
		return ;
	if (ft_abs(line.end.y - line.start.y) < ft_abs(line.end.x - line.start.x))
	{
		if (line.start.x > line.end.x)
			return (draw_low(data, line.end, line.start));
		return (draw_low(data, line.start, line.end));
	}
	if (line.start.y > line.end.y)
		return (draw_high(data, line.end, line.start));
	return (draw_high(data, line.start, line.end));
}

/* void	create_line(t_data *data, t_point start, t_point end, int col)
{
	t_line	line;
	t_vec	v_start;
	t_vec	v_end;

	v_start = vec(data->obj, data->wld, (t_point){start.x, start.y,
		start.z, (t_col){0}});
	v_end = vec(data->obj, data->wld, (t_point){end.x, end.y,
		end.z, (t_col){0}});
	if (!calc_point(data, &line, &v_start, &v_end))
		return ;
	if (col == 0)
	{
		line.start.col = (t_col){0, 0, 0};
		line.end.col = (t_col){0, 0, 0};
	}
	else
		set_color(data, &line, start, end);
	if (!move_point(data, &line.start, &line.end))
		return ;
} */

void	draw_map(t_data *data, int color)
{
	int		i;
	int		j;

	i = -1;
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	while (++i < data->obj.mat.len)
	{
		j = -1;
		while (++j < data->obj.mat.wid)
		{
			if (i != data->obj.mat.len - 1)
				draw_line(data,
					vec(data->obj, data->wld, (t_point){j, i,
						data->obj.mat.matrix[i][j], (t_col){0}}),
					vec(data->obj, data->wld, (t_point){j, i + 1,
						data->obj.mat.matrix[i + 1][j], (t_col){0}}), color);
			if (j != data->obj.mat.wid - 1)
				draw_line(data,
					vec(data->obj, data->wld, (t_point){j, i,
						data->obj.mat.matrix[i][j], (t_col){0}}),
					vec(data->obj, data->wld, (t_point){j + 1, i,
						data->obj.mat.matrix[i][j + 1], (t_col){0}}), color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
