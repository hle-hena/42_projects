/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 13:14:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/05 13:15:41 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mlx_close(t_data *data)
{
	mlx_del(data);
	ft_pend_prog(0, "Program Ended.");
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		mlx_close(data);
	if (keycode == 119 || keycode == 115 || keycode == 97 || keycode == 100
		|| keycode == 117 || keycode == 106 || keycode == 105
		|| keycode == 107 || keycode == 111 || keycode == 108 || keycode == 32
		|| keycode == 113 || keycode == 101)
	{
		draw_map(data, 0);
		if (keycode == 32)
		{
			data->proj = !data->proj;
			go_to_proj(data);
		}
		else if (keycode == 119 || keycode == 115 || keycode == 100
			|| keycode == 97 || keycode == 113 || keycode == 101)
			move(data, keycode);
		else if (keycode == 117 || keycode == 106 || keycode == 105
			|| keycode == 107 || keycode == 111 || keycode == 108)
			do_rot(&data->wld.cam.rot, &data->wld.base, keycode);
		draw_map(data, 1);
	}
	return (0);
}

int	mouse_wheel_hook(int button, int x, int y, t_data *data)
{
	x = x + 1;
	y = y + 1;
	if ((button == 4 || button == 5) && data->proj == 0)
		draw_map(data, 0);
	if (button == 4 && data->proj == 0)
	{
		data->wld.cam.scale += 1;
	}
	else if (button == 5 && data->wld.cam.scale != 1 && data->proj == 0)
	{
		data->wld.cam.scale -= 1;
	}
	if ((button == 4 || button == 5) && data->proj == 0)
		draw_map(data, 1);
	return (1);
}
