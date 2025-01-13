/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/13 17:04:39 by hle-hena         ###   ########.fr       */
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

void	add_rot(float *val, float *rot, float sign, int axis)
{
	t_data	*data;

	data = get_data();
	*val += data->modif.rot_speed * sign * (M_PI / 180) * data->d_time;
	*rot = data->modif.rot_speed * sign * (M_PI / 180) * data->d_time;
	if (*val >= (float)(2 * M_PI))
		*val = 0;
	else if (*val <= (float)-(2 * M_PI))
		*val = 0;
	*val = round_float(*val, 5);
	if (data->proj)
		block_rot(val, rot, axis);
}

void	do_rot(t_vec *cam_r, t_base *base, float sign, int axis)
{
	t_vec	rot;
	t_data	*data;
	float	angle;

	data = get_data();
	rot = (t_vec){1 * (axis == 1), 0, (1 * axis == 3)};
	if (axis == 1)
		add_rot(&cam_r->x, &angle, sign, axis);
	else if (axis == 2)
	{
		if (data->proj)
			rot = base->k;
		else
			rot = (t_vec){-base->k.x, -base->k.y, -base->k.z};
		add_rot(&cam_r->y, &angle, sign, axis);
	}
	else
		add_rot(&cam_r->z, &angle, sign, axis);
	base->i = rotate_vector_by_quaternion(base->i,
			axis_angle_to_quaternion(angle, rot));
	base->j = rotate_vector_by_quaternion(base->j,
			axis_angle_to_quaternion(angle, rot));
	base->k = rotate_vector_by_quaternion(base->k,
			axis_angle_to_quaternion(angle, rot));
	orthonormalize_base(base);
}
