/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:50:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/05 14:48:26 by hle-hena         ###   ########.fr       */
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
	t_trig	rot_y;
	t_trig	rot_x;
	t_trig	rot_z;

	if (!data->proj)
		data->wld.cam.ori.y += -sign * (data->wld.cam.scale);
	else
	{
		rot_y = (t_trig){sin(-data->wld.cam.rot.y), cos(-data->wld.cam.rot.y)};
		rot_x = (t_trig){sin(-data->wld.cam.rot.x), cos(-data->wld.cam.rot.x)};
		rot_z = (t_trig){sin(-data->wld.cam.rot.z), cos(-data->wld.cam.rot.z)};
		data->wld.cam.base.i = data->wld.init.i;
		do_rot_yxz(&data->wld.cam.base.i, rot_y, rot_x, rot_z);
		// look_at(&data->wld.cam.base, data->wld.cam.init,
		// 	(t_vec){-data->wld.cam.rot.x, -data->wld.cam.rot.y,
		// 	-data->wld.cam.rot.z});
		data->wld.cam.ori.x += -sign * (5)
			* data->wld.cam.base.i.z;
		data->wld.cam.ori.y += sign * (5)
			* data->wld.cam.base.i.x;
	}
}

void	move_side(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.x += -sign * (data->wld.cam.scale);
	else
	{
		look_at(&data->wld.cam.base, data->wld.cam.init,
			(t_vec){-data->wld.cam.rot.x, -data->wld.cam.rot.y,
			-data->wld.cam.rot.z});
		data->wld.cam.ori.x += -sign * (5)
			* data->wld.cam.base.j.z;
		data->wld.cam.ori.y += sign * (5)
			* data->wld.cam.base.j.x;
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
