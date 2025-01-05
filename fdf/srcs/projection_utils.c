/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:04:40 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/05 13:17:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	move_point_w(t_data *data, t_point *change, t_point other, int bord)
{
	int		border;
	float	param;
	t_point	n_point;

	if (other.x == change->x)
		return (1);
	if (bord)
		border = 0;
	else
		border = data->win_wid;
	param = (float)(border - change->x) / (other.x - change->x);
	if (param < 0 || param > 1)
		return (1);
	n_point = (t_point){border,
		change->y + param * (other.y - change->y),
		change->z + param * (other.z - change->z),
		get_grad(*change, other, param)};
	*change = n_point;
	return (0);
}

int	move_point_l(t_data *data, t_point *change, t_point other, int bord)
{
	int		border;
	float	param;
	t_point	n_point;

	if (other.y == change->y)
		return (1);
	if (bord)
		border = 0;
	else
		border = data->win_len;
	param = (float)(border - change->y) / (other.y - change->y);
	if (param > 1 || param < 0)
		return (1);
	n_point = (t_point){change->x + param * (other.x - change->x),
		border,
		change->z + param * (other.z - change->z),
		get_grad(*change, other, param)};
	*change = n_point;
	return (0);
}

int	move_point(t_data *data, t_point *start, t_point *end)
{
	int	res;

	res = 0;
	if (start->x > data->win_wid || start->x < 0)
		res += move_point_w(data, start, *end, start->x < 0);
	if (end->x > data->win_wid || end->x < 0)
		res += move_point_w(data, end, *start, end->x < 0);
	if (start->y > data->win_len || start->y < 0)
		res += move_point_l(data, start, *end, start->y < 0);
	if (end->y > data->win_len || end->y < 0)
		res += move_point_l(data, end, *start, end->y < 0);
	if (res != 0)
		return (0);
	return (1);
}

void	change_point(t_vec *change, t_vec other, int z)
{
	float	param;
	t_vec	n_point;

	param = (float)(z - change->z) / (other.z - change->z);
	n_point = (t_vec){change->x + param * (other.x - change->x),
		change->y + param * (other.y - change->y), z};
	*change = n_point;
}

void	go_to_proj(t_data *data)
{
	if (data->proj)
	{
		data->wld.cam.ori = (t_vec){0, -data->obj.mat.len
			* (15), 10 * (15)};
		data->wld.cam.rot = (t_vec){115 * (M_PI / 180),
			0 * (M_PI / 180), 0};
		data->wld.cam.scale = (15);
		look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
	}
	else if (!data->proj)
	{
		data->wld.cam.rot = (t_vec){
			-25 * (M_PI / 180),
			156 * (M_PI / 180),
			-140 * (M_PI / 180)
		};
		look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
		data->wld.cam.ori = (t_vec){0, 0, 0};
		data->wld.cam.scale = data->wld.init_scale;
	}
}