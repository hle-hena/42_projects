/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/19 20:10:18 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_obj(t_obj *obj, char *path)
{
	parse_file(&obj->mat, path);
	obj->ori.x = obj->mat.wid / 2;
	obj->ori.y = obj->mat.len / 2;
	obj->ori.z = 0;
	obj->base = (t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}};
	obj->rot = (t_vec){0, 0, 0};
	obj->scale = 1;
}

void	init_data(t_data *data, char **path)
{
	int	len;
	int	wid;
	
	init_obj(&data->obj, path[0]);
	data->disp = (t_disp){1, 1,
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, -1, 0}, (t_vec){0, 0, 0.1}},
		(t_cam){(t_vec){0, 0, 0}, (t_vec){0, 0, 0}}};
	data->disp.cam.rot.x = -27 * (M_PI / 180);
	data->disp.cam.rot.y = 39 * (M_PI / 180);
	data->disp.cam.rot.z = 54 * (M_PI / 180);
	//init the rotation of the camera to whatever you want here
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &len, &wid);
	data->disp.scale = ft_min(len / (data->obj.mat.len * 3),
			wid / (data->obj.mat.wid * 3));
	data->disp.init_scale = data->disp.scale;
	do_rot(&data->disp.base, data->disp.cam.rot);
	data->win_len = data->obj.mat.len * (data->disp.init_scale * 3);
	data->win_wid = data->obj.mat.wid * (data->disp.init_scale * 3);
	data->disp.cam.ori.x = -data->obj.mat.wid * data->disp.scale * 1.5;
	data->disp.cam.ori.y = -data->obj.mat.len * data->disp.scale * 1.5;
	data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len, "Fdf");
	data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
}

/* void	init_data(t_data *data, char *path)
{
	int	len;
	int	wid;

	init_matrix(&data->obj.mat, path);
	data->disp = (t_disp){1, 1, 0, 0, 0, (t_vec){1, 0, 0}, (t_vec){0, 1, 0},
		(t_vec){0, 0, 1}, (t_vec){0, 0, 0}, (t_vec){0, 0, 0}, 0, 0, 0};
	data->disp.rot_x = 90 * (M_PI / 180);
	data->disp.rot_y = 0 * (M_PI / 180);
	data->disp.rot_z = 0 * (M_PI / 180);
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &len, &wid);
	data->disp.scale = ft_min((len - 20) / (data->mat.len * 3),
			(wid - 20) / (data->mat.wid * 3));
	data->disp.init_scale = data->disp.scale;
	data->disp.rot_cen.x = (data->mat.wid + 1) / 2;
	// data->disp.rot_cen.x = 1;
	data->disp.rot_cen.y = data->mat.len / 2;
	// data->disp.rot_cen.y = 1;
	data->disp.rot_cen.z = 0;
	do_rot(data);
	// data->disp.rot_x = 180 * (M_PI / 180);
	// do_rot(data);
	// data->disp.rot_x = 270 * (M_PI / 180);
	// do_rot(data);
	data->disp.d_x = data->mat.wid;
	data->disp.d_y = data->mat.len;
	data->win = mlx_new_window(data->mlx, data->mat.wid * (data->disp.init_scale
				* 3), data->mat.len * (data->disp.init_scale * 3), "Fdf");
	data->img = mlx_new_image(data->mlx, data->mat.wid * (data->disp.init_scale
				* 3), data->mat.len * (data->disp.init_scale * 3));
} */
