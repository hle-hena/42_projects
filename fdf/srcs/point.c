/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 09:38:31 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 10:33:29 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_vec	vec(t_obj obj, t_wld wld, t_point point)
{
	t_point	wld_coo;
	t_vec	centered;
	t_vec	final;

	wld_coo = get_wld_coo(point, obj, wld);
	centered = (t_vec){wld_coo.x - wld.cam.ori.x, wld_coo.y - wld.cam.ori.y,
		wld_coo.z - wld.cam.ori.z};
	final.x = centered.x * wld.base.i.x + centered.y * wld.base.j.x
		+ centered.z * wld.base.k.x;
	final.y = centered.x * wld.base.i.y + centered.y * wld.base.j.y
		+ centered.z * wld.base.k.y;
	final.z = centered.x * wld.base.i.z + centered.y * wld.base.j.z
		+ centered.z * wld.base.k.z;
	round_vec(&final);
	return (final);
}
