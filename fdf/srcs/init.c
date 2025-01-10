/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:47:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/09 10:10:51 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* void	print_map(t_obj obj, int **tab)
{
	int		i;
	int		j;

	printf("Map :\n");
	i = -1;
	while (++i < obj.mat.len)
	{
		j = -1;
		while (++j < obj.mat.wid - 1)
		{
			printf("%d ", tab[i][j]);
		}
		printf("%d\n", tab[i][j]);
	}
	printf("\n\n");
} */

void	init_obj(t_obj *obj, char *path)
{
	obj->wld_ori = (t_point){0, 0, 0, (t_col){0}};
	obj->r_ori = (t_vec){0, 0, 0};
	obj->base = (t_base){(t_vec){0.849, 0, 0}, (t_vec){0, 0.97, 0},
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
		200 * (15)
	},
		1
	};
}

void	init_data(t_data *data, char **path)
{
	int	len;
	int	wid;

	data->event = (t_event){0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	init_obj(&data->obj, path[0]);
	init_wld(&data->wld);
	data->mlx = mlx_init();
	mlx_get_screen_size(data->mlx, &wid, &len);
	len *= 0.9;
	data->wld.init_scale = ft_min(len / (data->obj.mat.len * 3),
			wid / (data->obj.mat.wid * 3));
	if (data->wld.init_scale < 1)
		data->wld.init_scale = 1;
	data->wld.cam.scale = data->wld.init_scale;
	look_at(&data->wld.base, data->wld.init, data->wld.cam.rot);
	// data->win_len = (data->obj.mat.len) * (data->wld.init_scale * 3);
	// data->win_wid = (data->obj.mat.wid) * (data->wld.init_scale * 3);
	// if (data->win_len > len)
	// 	data->win_len = len;
	// if (data->win_wid > wid)
	// 	data->win_wid = wid;
	data->win_len = len;
	data->win_wid = wid;
	data->win = mlx_new_window(data->mlx, data->win_wid, data->win_len, "Fdf");
	data->img = mlx_new_image(data->mlx, data->win_wid, data->win_len);
}
