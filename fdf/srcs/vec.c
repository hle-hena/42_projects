/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:38:31 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/10 13:03:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec	normalize(t_vec v)
{
	float	mag;

	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return ((t_vec){v.x / mag, v.y / mag, v.z / mag});
}

t_vec	cross_product(t_vec a, t_vec b)
{
	return ((t_vec){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

void	orthonormalize_base(t_base *base)
{
	t_data	*data;

	data = get_data();
	base->i = normalize(base->i);
	base->j = normalize(base->j);
	if (data->proj)
		base->k = cross_product(base->j, base->i);
	else
		base->k = cross_product(base->i, base->j);
	base->k = normalize(base->k);
	if (data->proj)
		base->j = cross_product(base->i, base->k);
	else
		base->j = cross_product(base->k, base->i);
	base->j = normalize(base->j);
}

t_point	get_wld_coo(t_point point, t_obj obj, t_wld wld)
{
	t_point	centered;
	t_point	wld_coo;
	int		scale_factor;

	scale_factor = obj.scale * wld.cam.scale * 2;
	centered.x = point.x - obj.mat_ori.x;
	centered.y = point.y - obj.mat_ori.y;
	centered.z = point.z - obj.mat_ori.z;
	wld_coo.x = (centered.x * obj.base.i.x + centered.y * obj.base.j.x
			+ centered.z * obj.base.k.x) * scale_factor;
	wld_coo.y = (centered.x * obj.base.i.y + centered.y * obj.base.j.y
			+ centered.z * obj.base.k.y) * scale_factor;
	wld_coo.z = (centered.x * obj.base.i.z + centered.y * obj.base.j.z
			+ centered.z * obj.base.k.z) * scale_factor;
	wld_coo.x -= obj.wld_ori.x;
	wld_coo.y -= obj.wld_ori.y;
	wld_coo.z -= obj.wld_ori.z;
	return (wld_coo);
}

t_vec	vec(t_obj obj, t_wld wld, t_point point)
{
	t_point	wld_coo;
	t_vec	final;
	float	cam_x;
	float	cam_y;
	float	cam_z;

	wld_coo = get_wld_coo(point, obj, wld);
	cam_x = wld_coo.x - wld.cam.ori.x;
	cam_y = wld_coo.y - wld.cam.ori.y;
	cam_z = wld_coo.z - wld.cam.ori.z;
	final.x = cam_x * wld.base.i.x + cam_y * wld.base.j.x
		+ cam_z * wld.base.k.x;
	final.y = cam_x * wld.base.i.y + cam_y * wld.base.j.y
		+ cam_z * wld.base.k.y;
	final.z = cam_x * wld.base.i.z + cam_y * wld.base.j.z
		+ cam_z * wld.base.k.z;
	return (final);
}