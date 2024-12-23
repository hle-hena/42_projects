/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/23 16:02:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_high(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	t_vec	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dx) - dy;
	curr = (t_vec){start.x, start.y, start.z};
	while (curr.y <= end.y)
	{
		if (pixel_is_in_fov(data, curr))
			put_pixel(data, (t_point){curr.x, curr.y, curr.z, (t_col){0}},
				get_color(start, end, curr.z));
		if (err > 0)
		{
			curr.x += ft_tern_int(dx < 0, -1, 1);
			err += 2 * (ft_abs(dx) - dy);
		}
		else
			err += 2 * ft_abs(dx);
		curr.y += 1;
		curr.z = (float)(curr.y - start.y) / (end.y - start.y);
		curr.z = round_to_n_places(curr.z, 6);
	}
}

//color = get_color(curr, start, end);
//curr.z = (curr.x / (end.x - start.x)) * (end.z - start.z);
void	draw_low(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	t_vec	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dy) - dx;
	curr = (t_vec){start.x, start.y, start.z};
	while (curr.x <= end.x)
	{
		if (pixel_is_in_fov(data, curr))
			put_pixel(data, (t_point){curr.x, curr.y, curr.z, (t_col){0}},
				get_color(start, end, curr.z));
		if (err > 0)
		{
			curr.y += ft_tern_int(dy < 0, -1, 1);
			err += 2 * (ft_abs(dy) - dx);
		}
		else
			err += 2 * ft_abs(dy);
		curr.x += 1;
		curr.z = (float)(curr.x - start.x) / (end.x - start.x);
		curr.z = round_to_n_places(curr.z, 6);
	}
}

void	draw_line(t_data *data, t_point start, t_point end)
{
	if ((start.x >= (data->obj.mat.wid + 4) * data->wld.init_scale * 3
			|| start.x < 0
			|| start.y >= (data->obj.mat.len + 4) * data->wld.init_scale * 3
			|| start.y < 0)
		&& (end.x >= (data->obj.mat.wid + 4) * data->wld.init_scale * 3
			|| end.x < 0
			|| end.y >= (data->obj.mat.len + 4) * data->wld.init_scale * 3
			|| end.y < 0))
		return ;
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

	// printf("Base is %f\t%f\t%f\n%f\t%f\t%f\n%f\t%f\t%f\n",
	// 	data->wld.base.i.x, data->wld.base.i.y, data->wld.base.i.z,
	// 	data->wld.base.j.x, data->wld.base.j.y, data->wld.base.j.z,
	// 	data->wld.base.k.x, data->wld.base.k.y, data->wld.base.k.z);
	// printf("Rot is \n%f\n%f\n%f\n", data->wld.cam.rot.x / (M_PI / 180),
	// 	data->wld.cam.rot.y / (M_PI / 180),
	// 	data->wld.cam.rot.z / (M_PI / 180));
	// printf("Cam ori is %f\t%f\t%f\n", data->wld.cam.ori.x,
	// 	data->wld.cam.ori.y, data->wld.cam.ori.z);
void	draw_map(t_data *data, int color)
{
	int		i;
	int		j;

	i = -1;
	while (++i < data->obj.mat.len - 1)
	{
		j = -1;
		while (++j < data->obj.mat.wid)
		{
			if (i != data->obj.mat.len - 2)
				draw_line(data, 
					point(data->obj, data->wld, (t_point){j, i,
						data->obj.mat.matrix[i][j], (t_col){0}}, color),
					point(data->obj, data->wld, (t_point){j, i + 1,
						data->obj.mat.matrix[i + 1][j], (t_col){0}}, color));
			if (j != data->obj.mat.wid - 1)
				draw_line(data,
					point(data->obj, data->wld, (t_point){j, i,
						data->obj.mat.matrix[i][j], (t_col){0}}, color),
					point(data->obj, data->wld, (t_point){j + 1, i,
						data->obj.mat.matrix[i][j + 1], (t_col){0}}, color));
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
