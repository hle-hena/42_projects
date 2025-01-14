/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_persp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:37:44 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/14 18:40:42 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_obj_coo(t_wld wld, t_obj obj)
{
	t_point	cam_coo;
	int		scale_factor;

	scale_factor = obj.scale * wld.cam.scale * 2;
	cam_coo.x = (wld.cam.ori.x / scale_factor) - obj.wld_ori.x
		+ obj.mat_ori.x + 0.5;
	cam_coo.y = (wld.cam.ori.y / scale_factor) - obj.wld_ori.y
		+ obj.mat_ori.y + 0.5;
	cam_coo.z = (wld.cam.ori.z / scale_factor) - obj.wld_ori.z
		+ obj.mat_ori.z + 0.5;
	return (cam_coo);
}

// start.x = left
// start.y = right
void	draw_for(t_data *data, int color, t_point pt, t_point inc)
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

void	draw_side(t_data *data, int color, t_point pt, t_point inc)
{
	int	start;

	start = pt.y;
	while (pt.x != inc.z)
	{
		pt.y = start;
		while (pt.y != pt.z)
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
			pt.y += inc.y;
		}
		pt.x += inc.x;
	}
	if (color)
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

// Look at base.i.x, 
// 	between 0.5 and 1.0 is looking forward
// 	between -0.5 and 0.5 is looking to a side
// 	between -0.5 and -1 is looking backward
// base.j.x for side
// 	negative means left, positive means right
// void	draw_persp(t_data *data, int color)
// {
// 	if (data->wld.cam.base.i)
// }

void	draw_persp(t_data *data, int color)
{
	data->obj.r_ori = vec(data->obj, data->wld, data->obj.wld_ori);
	if (data->wld.base.i.x >= 0.5)
		draw_for(data, color, (t_point){0, 0, data->obj.mat.len, (t_col){0}},
			(t_point){1, 1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x > -0.5 && data->wld.base.i.x < 0.5
		&& data->wld.base.j.x > 0)
		draw_side(data, color, (t_point){data->obj.mat.wid - 1, 0,
			data->obj.mat.len, (t_col){0}}, (t_point){-1, 1, -1, (t_col){0}});
	else if (data->wld.base.i.x > -0.5 && data->wld.base.i.x < 0.5
		&& data->wld.base.j.x < 0)
		draw_side(data, color, (t_point){0, data->obj.mat.len - 1, -1,
			(t_col){0}}, (t_point){1, -1, data->obj.mat.wid, (t_col){0}});
	else if (data->wld.base.i.x <= -0.5)
		draw_for(data, color, (t_point){data->obj.mat.wid - 1, data->obj.mat.len
			- 1, -1, (t_col){0}}, (t_point){-1, -1, -1, (t_col){0}});
}
