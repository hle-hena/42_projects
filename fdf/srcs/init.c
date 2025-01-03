/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/03 20:01:12 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_obj(t_obj *obj, char *path)
{
	obj->wld_ori = (t_point){0, 0, 0, (t_col){0}};
	obj->r_ori = (t_vec){0, 0, 0};
	obj->base = (t_base){(t_vec){0.849, 0, 0}, (t_vec){0, -0.97, 0},
		(t_vec){0, 0, 0.15}};
	obj->init = (t_base){(t_vec){0.849, 0, 0}, (t_vec){0, -0.97, 0},
		(t_vec){0, 0, 0.15}};
	obj->rot = (t_vec){0, 0, 0};
	obj->scale = 1;
	obj->max_h = 0;
	obj->min_h = 0;
	parse_file(&obj->mat, path, obj);
	obj->mat_ori.x = obj->mat.wid / 2;
	obj->mat_ori.y = obj->mat.len / 2;
	obj->mat_ori.z = 0;
	obj->max_h *= 0.15;
	obj->min_h *= 0.15;
}

void	init_wld(t_wld *wld)
{
	*wld = (t_wld)
	{
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}},
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}},
		(t_cam)
	{
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}},
		(t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0}, (t_vec){0, 0, 1}},
		(t_vec){0, 0, 0},
		(t_vec){0, 0, 0},
	{
		-25 * (M_PI / 180),
		156 * (M_PI / 180),
		-140 * (M_PI / 180)
	},
		1,
		1,
		100 * (15)
	},
		1
	};
}

void	init_data(t_data *data, char **path)
{
	int	len;
	int	wid;

	init_obj(&data->obj, path[0]);
	init_wld(&data->wld);
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &wid, &len);
	len *= 0.9;
	data->wld.init_scale = ft_min(len / (data->obj.mat.len * 3),
			wid / (data->obj.mat.wid * 3));
	data->wld.cam.scale = data->wld.init_scale;
	look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
	data->win_len = (data->obj.mat.len) * (data->wld.init_scale * 3);
	data->win_wid = (data->obj.mat.wid)* (data->wld.init_scale * 3);
	data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len, "Fdf");
	data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
}
