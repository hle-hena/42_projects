/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/13 16:13:31 by hle-hena         ###   ########.fr       */
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
	if (!move_point(data, &line.start, &line.end))
		return (0);
	if (col == 0)
	{
		line.start.col = (t_col){0, 0, 0};
		line.end.col = (t_col){0, 0, 0};
	}
	else
		get_color(data, &line, start, end);
	draw_line(data, line.start, line.end);
	return (1);
}

void	draw_iso(t_data *data, int color, t_point pt, t_point inc)
{
	int	start;

	start = pt.x;
	while (pt.y != pt.z)
	{
		pt.x = start;
		while (pt.x != inc.z)
		{
			if (pt.y != data->obj.mat.len - 1)
				create_line(data, (t_point){pt.x, pt.y,
					data->obj.mat.matrix[pt.y][pt.x], (t_col){0}}, (t_point){
					pt.x, pt.y + 1, data->obj.mat.matrix[pt.y + 1][pt.x],
					(t_col){0}}, color);
			if (pt.x != data->obj.mat.wid - 1)
				create_line(data, (t_point){pt.x, pt.y,
					data->obj.mat.matrix[pt.y][pt.x], (t_col){0}}, (t_point){
					pt.x + 1, pt.y, data->obj.mat.matrix[pt.y][pt.x + 1],
					(t_col){0}}, color);
			pt.x += inc.x;
		}
		pt.y += inc.y;
	}
	if (color)
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

	// if (data->proj)
	// 	return (draw_persp())
void	draw_map(t_data *data, int color)
{
	int	up;
	int	side;

	up = ft_tern_int(data->wld.base.k.z >= 0, 1, -1);
	side = ft_tern_int(data->wld.base.k.y <= 0, 1, -1);
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	if (data->wld.base.i.x * side >= 0
		&& data->wld.base.i.y * side * up >= 0)
		draw_iso(data, color, (t_point){0, 0, data->obj.mat.len, (t_col){0}},
			(t_point){1, 1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x * side > 0
		&& data->wld.base.i.y * side * up < 0)
		draw_iso(data, color, (t_point){data->obj.mat.wid - 1, 0,
			data->obj.mat.len, (t_col){0}}, (t_point){-1, 1, -1, (t_col){0}});
	else if (data->wld.base.i.x * side < 0
		&& data->wld.base.i.y * side * up > 0)
		draw_iso(data, color, (t_point){0, data->obj.mat.len - 1, -1,
			(t_col){0}}, (t_point){1, -1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x * side < 0
		&& data->wld.base.i.y * side * up < 0)
		draw_iso(data, color, (t_point){data->obj.mat.wid - 1, data->obj.mat.len
			- 1, -1, (t_col){0}}, (t_point){-1, -1, -1, (t_col){0}});
}
