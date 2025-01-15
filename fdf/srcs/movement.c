/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 10:50:22 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/15 17:24:12 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	go_up(t_data *data, int sign)
{
	data->wld.cam.ori.z += sign * data->modif.mo_speed * (10);
}

void	move_forward(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.y += sign * (data->wld.cam.scale) * data->d_time
			* data->modif.mo_speed;
	else
	{
		data->wld.cam.ori.x += sign * (10) * data->d_time
			* data->wld.cam.base.i.z * data->modif.mo_speed;
		data->wld.cam.ori.y += -sign * (10) * data->d_time
			* data->wld.cam.base.i.x * data->modif.mo_speed;
		if (data->modif.r_move)
			data->wld.cam.ori.z += -sign * (10) * data->d_time
				* ((data->wld.cam.rot.x - (90 * (M_PI / 180))) / 2)
				* data->modif.mo_speed;
	}
}

void	move_side(t_data *data, int sign)
{
	if (!data->proj)
		data->wld.cam.ori.x += -sign * (data->wld.cam.scale) * data->d_time
			* data->modif.mo_speed;
	else
	{
		data->wld.cam.ori.x += -sign * (10) * data->d_time
			* data->wld.cam.base.j.z * data->modif.mo_speed;
		data->wld.cam.ori.y += sign * (10) * data->d_time
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
