/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:12:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/02 20:18:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* t_point	*global_point(void)
{
	static t_point	global = (t_point){0, 0, 0};

	return (&global);
} */

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

int	mlx_close(t_data *data)
{
	mlx_del(data);
	ft_pend_prog(0, "Program Ended.");
	return (0);
}

void	add_rot(float *val, int sign)
{
	*val += 1 * sign * (M_PI / 180);
	if (*val >= (float)(2 * M_PI))
		*val -= 2 * M_PI;
	else if (*val <= (float)-(2 * M_PI))
		*val += 2 * M_PI;
	round_float(*val, 5);
}

void	go_forward(t_data *data, int sign)
{
	do_rot(&data->wld.cam.base, data->wld.cam.init,
		(t_vec){-data->wld.cam.rot.x, -data->wld.cam.rot.y,
			-data->wld.cam.rot.z});
	norm_vec(&data->wld.cam.base.k);
	data->wld.cam.ori.x += sign * (data->wld.cam.scale / 4) * data->wld.cam.base.k.x;
	data->wld.cam.ori.y += sign * (data->wld.cam.scale / 4) * data->wld.cam.base.k.y;
	// data->wld.cam.ori.z += sign * 4 * data->wld.base.k.z;
}

void	go_up(t_data *data, int sign)
{
	data->wld.cam.ori.z += sign;
}

void	go_side(t_data *data, int sign)
{
	data->wld.cam.ori.x += sign * 10 * (data->wld.cam.base.j.x
			+ data->wld.cam.base.j.y + data->wld.cam.base.j.z);
}

void	go_to_proj(t_data *data)
{
	if (data->proj)
	{
		data->wld.cam.ori = (t_vec){0, -data->obj.mat.len / 2,
			2 * data->wld.cam.scale};
		data->wld.cam.rot = (t_vec){90 * (M_PI / 180),
			-180 * (M_PI / 180), 0};
		data->wld.cam.scale = data->wld.init_scale;
	}
	else if (!data->proj)
	{
		data->wld.cam.rot = (t_vec){
			-19 * (M_PI / 180),
			25 * (M_PI / 180),
			40 * (M_PI / 180)
		};
		data->wld.cam.ori = (t_vec){0, 0, 0};
		data->wld.cam.scale = data->wld.init_scale;
	}
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
		else if (keycode == 119)
			go_forward(data, 1);
		else if (keycode == 115)
			go_forward(data, -1);
		else if (keycode == 97)
			go_side(data, 1);
		else if (keycode == 100)
			go_side(data, -1);
		else if (keycode == 113)
			go_up(data, 1);
		else if (keycode == 101)
			go_up(data, -1);
		else if (keycode == 117)
			add_rot(&data->wld.cam.rot.x, 1);
		else if (keycode == 106)
			add_rot(&data->wld.cam.rot.x, -1);
		else if (keycode == 105)
			add_rot(&data->wld.cam.rot.y, 1);
		else if (keycode == 107)
			add_rot(&data->wld.cam.rot.y, -1);
		else if (keycode == 111)
			add_rot(&data->wld.cam.rot.z, 1);
		else if (keycode == 108)
			add_rot(&data->wld.cam.rot.z, -1);
		if (keycode == 117 || keycode == 106 || keycode == 105
			|| keycode == 107 || keycode == 111 || keycode == 108
			|| keycode == 32)
			do_rot(&data->wld.base, data->wld.init, data->wld.cam.rot);
		draw_map(data, 1);
		// printf("Rot is %d\t%d\t%d\n", (int)((data->wld.cam.rot.x * 180) / M_PI),
		// 	(int)((180 * data->wld.cam.rot.y) / M_PI),
		// 	(int)((180 * data->wld.cam.rot.z) / M_PI));
	}
	return (0);
}
	// printf("Rot is %d\t%d\t%d\n", (int)((data->wld.cam.rot.x * 180) / M_PI),
	// 	(int)((180 * data->wld.cam.rot.y) / M_PI),
	// 	(int)((180 * data->wld.cam.rot.z) / M_PI));
	// printf("Scale is %d\n", data->wld.cam.scale);
	// printf("Camera is %f\t%f\t%f\n", data->wld.cam.ori.x,
	// 	data->wld.cam.ori.y, data->wld.cam.ori.z);
	// printf("\n\n");

/* int	move_hook(int x, int y, t_data *data)
{
	static t_point	last = {0, 0, 0};

	draw_line(data, *global_point(), last, 0x00000000);
	draw_line(data, *global_point(), (t_point){x, y, 0}, 0x00FFFFFF);
	last.x = x;
	last.y = y;
	return (1);
} */

int	mouse_wheel_hook(int button, int x, int y, t_data *data)
{
	x = x + 1;
	y = y + 1;
	if (button == 4 || button == 5)
		draw_map(data, 0);
	if (button == 4)
	{
		data->wld.cam.scale += 1;
	}
	else if (button == 5 && data->wld.cam.scale != 0)
	{
		data->wld.cam.scale -= 1;
	}
	if (button == 4 || button == 5)
		draw_map(data, 1);
	return (1);
}

	// mlx_hook(data->win, 6, 1L << 6, move_hook, data);
int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		ft_perror(2, 0, NULL);
	data = get_data();
	init_data(data, &av[1]);
	draw_map(data, 1);
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_wheel_hook, data);
	mlx_hook(data->win, 17, 0, mlx_close, data);
	mlx_loop(data->mlx);
}
