/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/22 15:12:22 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_obj(t_obj *obj, char *path)
{
	parse_file(&obj->mat, path);
	obj->mat_ori.x = obj->mat.wid / 2;
	obj->mat_ori.y = obj->mat.len / 2;
	obj->mat_ori.z = 0;
	obj->wld_ori = (t_vec){0, 0, 0};
	obj->base = (t_base){(t_vec){0.849, 0, 0}, (t_vec){0, 0.97, 0},
		(t_vec){0, 0, 0.15}};
	obj->init = (t_base){(t_vec){0.849, 0, 0}, (t_vec){0, 0.97, 0},
		(t_vec){0, 0, 0.15}};
	obj->rot = (t_vec){0, 0, 0};
	obj->scale = 1;
}

void	init_wld(t_wld *wld)
{
	*wld = (t_wld)
	{
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}},
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}},
		(t_cam)
	{
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, -1}},
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, -1}},
		// (t_vec){250, 30, 0},
		(t_vec){0, 0, 0},
	{
		// -19 * (M_PI / 180),
		// 25 * (M_PI / 180),
		// 40 * (M_PI / 180)
		-90 * (M_PI / 180),
		0 * (M_PI / 180),
		0 * (M_PI / 180)
	},
		1,
		-0.1,
		1
	},
		1
	};
	/* Rot is -24	27	39
Scale is 95
Camera is 1020.000000	160.000000	0.000000 */
}

void	init_data(t_data *data, char **path)
{
	int	len;
	int	wid;

	init_obj(&data->obj, path[0]);
	init_wld(&data->wld);
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &len, &wid);
	data->wld.init_scale = ft_min(len / (data->obj.mat.len * 3),
			wid / (data->obj.mat.wid * 3));
	data->wld.cam.scale = data->wld.init_scale;
	do_rot(&data->wld.cam.base, data->wld.cam.init, data->wld.cam.rot);
	data->win_len = data->obj.mat.len * (data->wld.init_scale * 3);
	data->win_wid = data->obj.mat.wid * (data->wld.init_scale * 3);
	data->wld.cam.scale = 45; /////////////////////////This is for test
	data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len, "Fdf");
	data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
}

/* void	init_data(t_data *data, char *path)
{
	int	len;
	int	wid;

	init_matrix(&data->obj.mat, path);
	data->wld = (t_wld){1, 1, 0, 0, 0, (t_vec){1, 0, 0}, (t_vec){0, 1, 0},
		(t_vec){0, 0, 1}, (t_vec){0, 0, 0}, (t_vec){0, 0, 0}, 0, 0, 0};
	data->wld.rot_x = 90 * (M_PI / 180);
	data->wld.rot_y = 0 * (M_PI / 180);
	data->wld.rot_z = 0 * (M_PI / 180);
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &len, &wid);
	data->wld.scale = ft_min((len - 20) / (data->mat.len * 3),
			(wid - 20) / (data->mat.wid * 3));
	data->wld.init_scale = data->wld.scale;
	data->wld.rot_cen.x = (data->mat.wid + 1) / 2;
	// data->wld.rot_cen.x = 1;
	data->wld.rot_cen.y = data->mat.len / 2;
	// data->wld.rot_cen.y = 1;
	data->wld.rot_cen.z = 0;
	do_rot(data);
	// data->wld.rot_x = 180 * (M_PI / 180);
	// do_rot(data);
	// data->wld.rot_x = 270 * (M_PI / 180);
	// do_rot(data);
	data->wld.d_x = data->mat.wid;
	data->wld.d_y = data->mat.len;
	data->win = mlx_new_window(data->mlx, data->mat.wid * (data->wld.init_scale
				* 3), data->mat.len * (data->wld.init_scale * 3), "Fdf");
	data->img = mlx_new_image(data->mlx, data->mat.wid * (data->wld.init_scale
				* 3), data->mat.len * (data->wld.init_scale * 3));
} */
