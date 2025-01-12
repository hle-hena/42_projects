/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:26:38 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/12 17:35:14 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_event(t_data *data)
{
	if (data->event.rot_y && !data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_y, 2);
	if (data->event.rot_x && !data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_x, 1);
	if (data->event.rot_z && !data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_z, 3);
	if (data->event.rp_y && data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rp_y, 2);
	if (data->event.rp_x && data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rp_x, 1);
	if (data->event.rp_x || data->event.rp_y)
	{
		data->event.rp_x = 0;
		data->event.rp_y = 0;
	}
}

void	move_event(t_data *data)
{
	if (data->event.mo_f)
		move_forward(data, data->event.mo_f);
	if (data->event.mo_s)
		move_side(data, data->event.mo_s);
}

void	scale_event(t_data *data)
{
	if (data->event.sc)
		data->wld.cam.scale += data->event.sc;
	if (data->wld.cam.scale < 1)
		data->wld.cam.scale = 1;
	if (data->event.sc)
		data->event.sc = 0;
}

void	fog_event(t_data *data)
{
	if (data->event.fog)
		data->wld.cam.fog += data->event.fog * 0.1;
}

int	event_loop(t_data *data)
{
	int		temp;
	int		fps;
	float	frame_start_time;

	frame_start_time = get_current_time();
	ft_bzero((void *)mlx_get_data_addr(data->img, &temp, &temp, &temp),
		data->win_len * data->win_wid * sizeof(int));
	fog_event(data);
	rotate_event(data);
	move_event(data);
	scale_event(data);
	draw_map(data, 1);
	fps = calculate_fps();
	if (fps != 0)
		data->d_time = TARGET_FPS / fps;
	limit_frame_rate(frame_start_time);
	return (1);
}
