/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/07 14:09:13 by hle-hena         ###   ########.fr       */
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

void	add_rot(float *val, float *rot, int sign, int axis)
{
	int		inc;
	t_data	*data;

	inc = 1;
	data = get_data();
	*val += inc * sign * (M_PI / 180);
	*rot = inc * sign * (M_PI / 180);
	if (*val >= (float)(2 * M_PI))
		*val -= 2 * M_PI;
	else if (*val <= (float)-(2 * M_PI))
		*val += 2 * M_PI;
	*val = round_float(*val, 5);
	if (data->proj)
		block_rot(val, rot, axis);
}

void	do_rot_a(t_base *base, t_vec rot)
{
	t_trig	rot_y;
	t_trig	rot_x;
	t_trig	rot_z;

	rot_y = (t_trig){sin(rot.y), cos(rot.y)};
	rot_x = (t_trig){sin(rot.x), cos(rot.x)};
	rot_z = (t_trig){sin(rot.z), cos(rot.z)};
	do_rot_yxz(&base->i, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->j, rot_y, rot_x, rot_z);
	do_rot_yxz(&base->k, rot_y, rot_x, rot_z);
}

void	do_rot(t_vec *cam_r, t_base *base, int sign, int axis)
{
	t_vec	rot;
	t_data	*data;

	data = get_data();
	rot = (t_vec){0, 0, 0};
	if (axis == 1)
		add_rot(&cam_r->x, &rot.x, sign, axis);
	else if (axis == 2)
		add_rot(&cam_r->y, &rot.y, sign, axis);
	else if (axis == 3)
		add_rot(&cam_r->z, &rot.z, sign, axis);
	if (data->proj && axis == 2)
		do_rot_a(base, (t_vec){((90 * (M_PI / 180)) - cam_r->x), 0, 0});
	do_rot_a(base, rot);
	if (data->proj && axis == 2)
		do_rot_a(base, (t_vec){((90 * (M_PI / 180)) * -1 - cam_r->x), 0, 0});
}
