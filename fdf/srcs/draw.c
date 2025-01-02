/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/02 11:58:15 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_high(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	float	percent;
	t_point	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dx) - dy;
	percent = 0;
	curr = (t_point){start.x, start.y, 0, (t_col){0}};
	while (curr.y <= end.y)
	{
		if (point_is_in_fov(data, curr))
			put_pixel(data, curr, calc_color(get_color(start, end, percent)));
		if (err > 0)
		{
			curr.x += ft_tern_int(dx < 0, -1, 1);
			err += 2 * (ft_abs(dx) - dy);
		}
		else
			err += 2 * ft_abs(dx);
		curr.y += 1;
		percent += (float)1 / dy;
	}
}

void	draw_low(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	float	percent;
	t_point	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dy) - dx;
	percent = 0;
	curr = (t_point){start.x, start.y, 0, (t_col){0}};
	while (curr.x <= end.x)
	{
		if (point_is_in_fov(data, curr))
			put_pixel(data, curr, calc_color(get_color(start, end, percent)));
		if (err > 0)
		{
			curr.y += ft_tern_int(dy < 0, -1, 1);
			err += 2 * (ft_abs(dy) - dx);
		}
		else
			err += 2 * ft_abs(dy);
		curr.x += 1;
		percent += (float)1 / dx;
	}
}

/* 	if ((start.x >= (data->obj.mat.wid + 4) * data->wld.init_scale * 3
			|| start.x < 0
			|| start.y >= (data->obj.mat.len + 4) * data->wld.init_scale * 3
			|| start.y < 0)
		&& (end.x >= (data->obj.mat.wid + 4) * data->wld.init_scale * 3
			|| end.x < 0
			|| end.y >= (data->obj.mat.len + 4) * data->wld.init_scale * 3
			|| end.y < 0))
		return ;
	if (start.z < 0 && end.z < 0)
		return ; */
void	draw_line(t_data *data, t_vec start, t_vec end, int	col)
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
	if (!point_is_in_fov(data, line.start) && !point_is_in_fov(data, line.end))
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

	// printf("Base is %f\t%f\t%f\n%f\t%f\t%f\n%f\t%f\t%f\n",
	// 	data->wld.base.i.x, data->wld.base.i.y, data->wld.base.i.z,
	// 	data->wld.base.j.x, data->wld.base.j.y, data->wld.base.j.z,
	// 	data->wld.base.k.x, data->wld.base.k.y, data->wld.base.k.z);
	// printf("Cam ori is %f\t%f\t%f\n", data->wld.cam.ori.x,
	// 	data->wld.cam.ori.y, data->wld.cam.ori.z);
void	draw_map(t_data *data, int color)
{
	int		i;
	int		j;

	i = -1;
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	while (++i < data->obj.mat.len - 1)
	{
		j = -1;
		while (++j < data->obj.mat.wid)
		{
			if (i != data->obj.mat.len - 2)
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
