/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/14 19:55:18 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	new_window(t_data *data)
{
	int		wid;
	int		len;

	data->control = !data->control;
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img);
	if (data->control)
	{
		data->win_wid *= 0.8;
		data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len,
				"Fdf - CONTROL");
		data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
	}
	else
	{
		mlx_get_screen_size(data->mlx, &wid, &len);
		data->win_wid = wid;
		data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len,
				"Fdf");
		data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
	}
	if (data->proj)
		mlx_mouse_hide(data->mlx, data->win);
	loop();
}

void	init_obj(t_obj *obj, char *path)
{
	obj->wld_ori = (t_point){0, 0, 0, (t_col){0}};
	obj->r_ori = (t_vec){0, 0, 0};
	obj->base = (t_base){(t_vec){1, 0, 0}, (t_vec){0, 1, 0},
		(t_vec){0, 0, 0.15}};
	obj->init = (t_base){(t_vec){0.849, 0, 0}, (t_vec){0, 0.97, 0},
		(t_vec){0, 0, 0.15}};
	obj->rot = (t_vec){0, 0, 0};
	obj->scale = 1;
	obj->max_h = 0;
	obj->min_h = 0;
	parse_file(obj, path);
	obj->mat_ori.x = obj->mat.wid / 2;
	obj->mat_ori.y = obj->mat.len / 2;
	obj->mat_ori.z = 0;
	set_color(obj);
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
		24 * (M_PI / 180),
		-24 * (M_PI / 180),
		37 * (M_PI / 180)
	},
		1,
		1 * (15),
	},
		1
	};
}

void	init_data(t_data *data, char **path)
{
	int	len;
	int	wid;

	data->control = 0;
	data->event = (t_event){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	data->modif = (t_modif){0, 4, 1, 1, 60, 200 * (15)};
	init_obj(&data->obj, path[0]);
	init_wld(&data->wld);
	data->d_time = 1;
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &wid, &len);
	len *= 0.9;
	data->wld.init_scale = ft_min(len / (data->obj.mat.len * 3),
			wid / (data->obj.mat.wid * 3));
	if (data->wld.init_scale < 1)
		data->wld.init_scale = 1;
	data->wld.cam.scale = data->wld.init_scale;
	look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
	data->win_len = len;
	data->win_wid = wid;
	data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len, "Fdf");
	data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
	update_terminal_status(data, 1);
}
