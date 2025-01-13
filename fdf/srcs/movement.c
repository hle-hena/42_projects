/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:50:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/13 12:34:50 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	go_up(t_data *data, int sign)
{
	data->wld.cam.ori.z += sign;
}

// printf("The vec i is {%f, %f, %f}\n", data->wld.cam.base.i.x,
// 	data->wld.cam.base.i.y, data->wld.cam.base.i.z);
// printf("The vec j is {%f, %f, %f}\n", data->wld.cam.base.j.x,
// 	data->wld.cam.base.j.y, data->wld.cam.base.j.z);
// printf("The vec k is {%f, %f, %f}\n", data->wld.cam.base.k.x,
// 	data->wld.cam.base.k.y, data->wld.cam.base.k.z);
void	move_forward(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.y += sign * (data->wld.cam.scale) * data->d_time
			* data->modif.mo_speed;
	else
	{
		data->wld.cam.base.i = data->wld.init.i;
		data->wld.cam.base.i = rotate_vector_by_quaternion(data->wld.cam.base.i,
				axis_angle_to_quaternion(data->wld.cam.rot.x,
					(t_vec){1, 0, 0}));
		data->wld.cam.base.i = rotate_vector_by_quaternion(data->wld.cam.base.i,
				axis_angle_to_quaternion(data->wld.cam.rot.y,
					(t_vec){0, 1, 0}));
		data->wld.cam.base.i = rotate_vector_by_quaternion(data->wld.cam.base.i,
				axis_angle_to_quaternion(data->wld.cam.rot.z,
					(t_vec){0, 0, 1}));
		data->wld.cam.ori.x += -sign * (10) * data->d_time
			* data->wld.cam.base.i.z * data->modif.mo_speed;
		data->wld.cam.ori.y += -sign * (10) * data->d_time
			* data->wld.cam.base.i.x * data->modif.mo_speed;
	}
}
		// data->wld.cam.ori.z += -sign * (5)
		// 	* data->wld.cam.base.i.y;

void	move_side(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.x += -sign * (data->wld.cam.scale) * data->d_time
			* data->modif.mo_speed;
	else
	{
		data->wld.cam.base.j = data->wld.init.j;
		data->wld.cam.base.j = rotate_vector_by_quaternion(data->wld.cam.base.j,
				axis_angle_to_quaternion(data->wld.cam.rot.x,
					(t_vec){1, 0, 0}));
		data->wld.cam.base.j = rotate_vector_by_quaternion(data->wld.cam.base.j,
				axis_angle_to_quaternion(data->wld.cam.rot.y,
					(t_vec){0, 1, 0}));
		data->wld.cam.base.j = rotate_vector_by_quaternion(data->wld.cam.base.j,
				axis_angle_to_quaternion(data->wld.cam.rot.z,
					(t_vec){0, 0, 1}));
		data->wld.cam.ori.x += -sign * (5) * data->d_time
			* data->wld.cam.base.j.z * data->modif.mo_speed;
		data->wld.cam.ori.y += -sign * (5) * data->d_time
			* data->wld.cam.base.j.x * data->modif.mo_speed;
	}
}

void	move(t_data *data, int keycode)
{
	if (keycode == 119)
		move_forward(data, 1);
	else if (keycode == 115)
		move_forward(data, -1);
	else if (keycode == 100)
		move_side(data, 1);
	else if (keycode == 97)
		move_side(data, -1);
	else if (keycode == 113)
		go_up(data, 1);
	else if (keycode == 101)
		go_up(data, -1);
}
