/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:14:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/07 10:20:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	event_loop(t_data *data)
{
	int	temp;

	if (data->event.mo_s || data->event.mo_f || data->event.rot_x
		|| data->event.rot_y || data->event.rot_z || data->event.sc)
		// draw_map(data, 0);
		ft_bzero((void *)mlx_get_data_addr(data->img, &temp, &temp, &temp), data->win_len * data->win_wid * sizeof(int));
	if (data->event.sc)
		data->wld.cam.scale += data->event.sc;
	if (data->event.rot_y)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_y, 2);
	if (data->event.rot_x)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_x, 1);
	if (data->event.rot_z)
		do_rot(&data->wld.cam.rot, &data->wld.base, data->event.rot_z, 3);
	if (data->event.mo_f)
		move_forward(data, data->event.mo_f);
	if (data->event.mo_s)
		move_side(data, data->event.mo_s);
	if (data->event.mo_s || data->event.mo_f || data->event.rot_x
		|| data->event.rot_y || data->event.rot_z || data->event.sc)
		draw_map(data, 1);
	if (data->event.sc != 0)
		data->event.sc = 0;
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_close(data);
	if (keycode == 119 || keycode == 115)
		data->event.mo_f = (keycode == 119) * 1 + (keycode == 115) * -1;
	else if (keycode == 100 || keycode == 97)
		data->event.mo_s = (keycode == 100) * 1 + (keycode == 97) * -1;
	else if (keycode == 117 || keycode == 106)
		data->event.rot_x = (keycode == 117) * 1 + (keycode == 106) * -1;
	else if (keycode == 105 || keycode == 107)
		data->event.rot_y = (keycode == 105) * 1 + (keycode == 107) * -1;
	else if (keycode == 111 || keycode == 108)
		data->event.rot_z = (keycode == 111) * 1 + (keycode == 108) * -1;
	// event_loop(data);
	return (0);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == 32)
	{
		draw_map(data, 0);
		data->proj = !data->proj;
		go_to_proj(data);
		draw_map(data, 1);
	}
	if (keycode == 119 || keycode == 115)
		data->event.mo_f = 0;
	else if (keycode == 100 || keycode == 97)
		data->event.mo_s = 0;
	else if (keycode == 117 || keycode == 106)
		data->event.rot_x = 0;
	else if (keycode == 105 || keycode == 107)
		data->event.rot_y = 0;
	else if (keycode == 111 || keycode == 108)
		data->event.rot_z = 0;
	return (0);
}

int	mouse_down(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 4 && data->proj == 0)
		data->event.sc = 1;
	else if (button == 5 && data->wld.cam.scale != 1 && data->proj == 0)
		data->event.sc -= 1;
	return (1);
}
