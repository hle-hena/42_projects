/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:12:54 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/06 17:32:38 by hle-hena         ###   ########.fr       */
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

	// mlx_hook(data->win, 6, 1L << 6, move_hook, data);
int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		ft_perror(2, 0, NULL);
	data = get_data();
	init_data(data, &av[1]);
	draw_map(data, 1);
	mlx_hook(data->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->win, 3, 1L << 1, key_down, data);
	mlx_hook(data->win, 4, 1L << 2, mouse_down, data);
	mlx_hook(data->win, 17, 0, mlx_close, data);
	mlx_loop_hook(data->mlx, event_loop, data);
	mlx_loop(data->mlx);
}
