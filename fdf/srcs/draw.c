/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/22 14:45:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_high(t_data *data, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	err;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dx) - dy;
	while (start.y <= end.y)
	{
		if (start.x < data->obj.mat.wid * data->wld.init_scale * 3 && start.x >= 0
			&& start.y < data->obj.mat.len * data->wld.init_scale * 3 && start.y >= 0)
			put_pixel(data, start, color);
		if (err > 0)
		{
			start.x += ft_tern_int(dx < 0, -1, 1);
			err += 2 * (ft_abs(dx) - dy);
		}
		else
			err += 2 * ft_abs(dx);
		start.y += 1;
	}
}

void	draw_low(t_data *data, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	err;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dy) - dx;
	while (start.x <= end.x)
	{
		if (start.x < data->obj.mat.wid * data->wld.init_scale * 3 && start.x >= 0
			&& start.y < data->obj.mat.len * data->wld.init_scale * 3 && start.y >= 0)
			put_pixel(data, start, color);
		if (err > 0)
		{
			start.y += ft_tern_int(dy < 0, -1, 1);
			err += 2 * (ft_abs(dy) - dx);
		}
		else
			err += 2 * ft_abs(dy);
		start.x += 1;
	}
}

	// if (color == 0)
	// 	color = color(start, end);
void	draw_line(t_data *data, t_point start, t_point end, int color)
{
	if ((start.x >= (data->obj.mat.wid + 4) * data->wld.init_scale * 3 || start.x < 0
			|| start.y >= (data->obj.mat.len + 4) * data->wld.init_scale * 3
			|| start.y < 0)
		&& (end.x >= (data->obj.mat.wid + 4) * data->wld.init_scale * 3 || end.x < 0
			|| end.y >= (data->obj.mat.len + 4) * data->wld.init_scale * 3
			|| end.y < 0))
		return ;
	if (start.z == 1 || end.z == 1)
		return;
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			return (draw_low(data, end, start, color));
		return (draw_low(data, start, end, color));
	}
	if (start.y > end.y)
		return (draw_high(data, end, start, color));
	return (draw_high(data, start, end, color));
}

void	draw_map(t_data *data, int color)
{
	int		i;
	int		j;

	// printf("Base is %f\t%f\t%f\n%f\t%f\t%f\n%f\t%f\t%f\n",
	// 	data->wld.base.i.x, data->wld.base.i.y, data->wld.base.i.z,
	// 	data->wld.base.j.x, data->wld.base.j.y, data->wld.base.j.z,
	// 	data->wld.base.k.x, data->wld.base.k.y, data->wld.base.k.z);
	// printf("Rot is \n%f\n%f\n%f\n", data->wld.cam.rot.x / (M_PI / 180),
		// data->wld.cam.rot.y / (M_PI / 180),
		// data->wld.cam.rot.z / (M_PI / 180));
	i = -1;
	if (color == -1)
		color = 0;
	while (++i < data->obj.mat.len - 1)
	{
		j = -1;
		while (++j < data->obj.mat.wid)
		{
			if (i != data->obj.mat.len - 2)
				draw_line(data, point(data->obj, data->wld, i, j),
					point(data->obj, data->wld, i + 1, j), color);
			if (j != data->obj.mat.wid - 1)
				draw_line(data, point(data->obj, data->wld, i, j),
					point(data->obj, data->wld, i, j + 1), color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
