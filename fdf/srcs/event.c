/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:26:38 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/08 15:26:56 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_event(t_data *data)
{
	if (data->event.rot_y/*  && !data->proj */)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_y, 2);
	if (data->event.rot_x/*  && !data->proj */)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_x, 1);
	if (data->event.rot_z/*  && !data->proj */)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_z, 3);
	if (data->event.rp_y && data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rp_y, 2);
	if (data->event.rp_x && data->proj)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rp_x, 1);
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
}

int	event_loop(t_data *data)
{
	int	temp;

	if (data->event.mo_s || data->event.mo_f || data->event.rot_x
		|| data->event.rot_y || data->event.rot_z || data->event.sc
		|| data->event.rp_x || data->event.rp_y)
		ft_bzero((void *)mlx_get_data_addr(data->img, &temp, &temp, &temp),
			data->win_len * data->win_wid * sizeof(int));
	rotate_event(data);
	move_event(data);
	scale_event(data);
	if (data->event.mo_s || data->event.mo_f || data->event.rot_x
		|| data->event.rot_y || data->event.rot_z || data->event.sc
		|| data->event.rp_x || data->event.rp_y)
		draw_map(data, 1);
	if (data->event.sc)
		data->event.sc = 0;
	if (data->event.rp_x || data->event.rp_y)
	{
		data->event.rp_x = 0;
		data->event.rp_y = 0;
	}
	return (1);
}
