/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/03 15:52:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	look_at(t_base *base, t_base init, t_vec rot)
{
	t_trig	rot_y;
	t_trig	rot_x;
	t_trig	rot_z;

	base->i = (t_vec){init.i.x, init.i.y, init.i.z};
	base->j = (t_vec){init.j.x, init.j.y, init.j.z};
	base->k = (t_vec){init.k.x, init.k.y, init.k.z};
	rot_y = (t_trig){sin(rot.y), cos(rot.y)};
	rot_x = (t_trig){sin(rot.x), cos(rot.x)};
	rot_z = (t_trig){sin(rot.z), cos(rot.z)};
	do_rot_yxz(&base->i, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->j, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->k, rot_y, rot_x, rot_z);
}

void	do_rot(t_vec *cam_r, t_base *base, int keycode)
{
	t_trig	rot_y;
	t_trig	rot_x;
	t_trig	rot_z;
	t_vec	rot;

	rot = (t_vec){0, 0, 0};
	if (keycode == 117)
		add_rot(&cam_r->x, &rot.x, 1);
	else if (keycode == 106)
		add_rot(&cam_r->x, &rot.x, -1);
	else if (keycode == 105)
		add_rot(&cam_r->y, &rot.y, 1);
	else if (keycode == 107)
		add_rot(&cam_r->y, &rot.y, -1);
	else if (keycode == 111)
		add_rot(&cam_r->z, &rot.z, 1);
	else if (keycode == 108)
		add_rot(&cam_r->z, &rot.z, -1);
	rot_y = (t_trig){sin(rot.y), cos(rot.y)};
	rot_x = (t_trig){sin(rot.x), cos(rot.x)};
	rot_z = (t_trig){sin(rot.z), cos(rot.z)};
	do_rot_yxz(&base->i, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->j, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->k, rot_y, rot_x, rot_z);
}
