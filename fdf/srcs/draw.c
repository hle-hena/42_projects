/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/05 11:41:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, t_point start, t_point end)
{
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			return (draw_low(data, end, start));
		return (draw_low(data, start, end));
	}
	if (start.y > end.y)
		return (draw_high(data, end, start));
	return (draw_high(data, start, end));
}

int	create_line(t_data *data, t_point start, t_point end, int col)
{
	t_line	line;
	t_vec	v_start;
	t_vec	v_end;

	v_start = vec(data->obj, data->wld, start);
	v_end = vec(data->obj, data->wld, end);
	if (!calc_point(data, &line, &v_start, &v_end))
		return (0);
	if (col == 0)
	{
		line.start.col = (t_col){0, 0, 0};
		line.end.col = (t_col){0, 0, 0};
	}
	else
		get_color(data, &line, start, end);
	if (!move_point(data, &line.start, &line.end))
		return (0);
	draw_line(data, line.start, line.end);
	return (1);
}

void	draw_map(t_data *data, int color)
{
	int	i;
	int	j;

	i = -1;
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	while (++i < data->obj.mat.len)
	{
		j = -1;
		while (++j < data->obj.mat.wid)
		{
			if (i != data->obj.mat.len - 1)
				create_line(data,
					(t_point){j, i, data->obj.mat.matrix[i][j], (t_col){0}},
					(t_point){j, i + 1, data->obj.mat.matrix[i + 1][j],
					(t_col){0}}, color);
			if (j != data->obj.mat.wid - 1)
				create_line(data,
					(t_point){j, i, data->obj.mat.matrix[i][j], (t_col){0}},
					(t_point){j + 1, i, data->obj.mat.matrix[i][j + 1],
					(t_col){0}}, color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
