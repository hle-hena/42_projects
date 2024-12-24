/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:38:31 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/24 17:43:59 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

		// if (z < data->wld.cam.near_plane)
		// 	return((t_point){x + (data->win_wid / 2),
		// 		y - 1 + (data->win_len), 1});
t_point	get_projection(int x, int y, int z, t_col color)
{
	t_data	*data;

	data = get_data();
	if (data->proj == 0)
	{
		return ((t_point){x + (data->win_wid / 2),
			y - 1 + (data->win_len / 2), z, color});
	}
	return ((t_point){x, y, z, color});
}

t_point	get_wld_coo(t_point point, t_obj obj, t_wld wld)
{
	t_point	centered;
	t_point	wld_coo;

	centered = (t_point){point.x - obj.mat_ori.x, point.y - obj.mat_ori.y,
		point.z - obj.mat_ori.z, (t_col){0}};
	wld_coo.x = (centered.x * obj.base.i.x + centered.y * obj.base.j.x
			+ centered.z * obj.base.k.x) * obj.scale * wld.cam.scale * 2;
	wld_coo.y = (centered.x * obj.base.i.y + centered.y * obj.base.j.y
			+ centered.z * obj.base.k.y) * obj.scale * wld.cam.scale * 2;
	wld_coo.z = (centered.x * obj.base.i.z + centered.y * obj.base.j.z
			+ centered.z * obj.base.k.z) * obj.scale * wld.cam.scale * 2;
	return ((t_point){wld_coo.x - obj.wld_ori.x, wld_coo.y - obj.wld_ori.y,
		wld_coo.z - obj.wld_ori.z, (t_col){0}});
}

t_point	point(t_obj obj, t_wld wld, t_point point, int color)
{
	t_vec	final;
	t_col	col;

	final = calc_vec(obj, wld, point);
	if (!color)
		col = (t_col){0, 0, 0};
	else
		col = get_real_color(obj, wld, final);
		// col = (t_col){0xFF, 0xFF, 0xFF};
	return (get_projection(final.x, final.y, final.z, col));
}

t_vec	calc_vec(t_obj obj, t_wld wld, t_point point)
{
	t_point	wld_coo;
	t_vec	centered;
	t_vec	final;

	wld_coo = get_wld_coo(point, obj, wld);
	centered = (t_vec){wld_coo.x - wld.cam.ori.x, wld_coo.y - wld.cam.ori.y,
		wld_coo.z - wld.cam.ori.z};
	round_vec(&centered);
	final.x = centered.x * wld.cam.base.i.x + centered.y * wld.cam.base.j.x
		+ centered.z * wld.cam.base.k.x;
	final.y = centered.x * wld.cam.base.i.y + centered.y * wld.cam.base.j.y
		+ centered.z * wld.cam.base.k.y;
	final.z = centered.x * wld.cam.base.i.z + centered.y * wld.cam.base.j.z
		+ centered.z * wld.cam.base.k.z;
	round_vec(&final);
	return (final);
}

/* int	get_color(t_data *data, t_vec curr, int color)
{
	float	percent;

	if (color == -1)
		return (0);
	percent = (data->wld.cam.base.k.x * (curr.x - data->obj.wld_ori.x)
			+ data->wld.cam.base.k.y * (curr.y - data->obj.wld_ori.y)
			+ data->wld.cam.base.k.z * (curr.z - data->obj.wld_ori.z))
			/ sqrt(ft_pow(data->wld.cam.base.k.x, 2)
				+ ft_pow(data->wld.cam.base.k.y, 2)
				+ ft_pow(data->wld.cam.base.k.z, 2));
	percent = percent * 100 / data->obj.max_h;
	if (percent <= 0.5 && percent >= 0)
		return (0x00FFFFFF + (0x00FFFB7D - 0x00FFFFFF) * (percent / 50));
	else if (percent > 0.5)
		return (0x00FFFB7D + (0x00FF4BF3 - 0x00FFFB7D) * ((percent - 50) / 50));
	return (0);
} */