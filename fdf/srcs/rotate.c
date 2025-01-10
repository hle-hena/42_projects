/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/09 18:45:31 by hle-hena         ###   ########.fr       */
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
	int		inc;
	t_data	*data;

	inc = 1;
	data = get_data();
	*val += inc * sign * (M_PI / 180);
	*rot = inc * sign * (M_PI / 180);
	if (*val >= (float)(2 * M_PI))
		*val -=0;
	else if (*val <= (float)-(2 * M_PI))
		*val += 0;
	*val = round_float(*val, 5);
	if (data->proj)
		block_rot(val, rot, axis);
}

// Normalize a vector
t_vec normalize(t_vec v)
{
    float mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (t_vec){v.x / mag, v.y / mag, v.z / mag};
}

// Cross product of two vectors
t_vec cross_product(t_vec a, t_vec b)
{
    return (t_vec){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

void orthonormalize_base(t_data *data, t_base *base)
{
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

void	do_rot(t_vec *cam_r, t_base *base, float sign, int axis)
{
	t_vec	rot;
	t_data	*data;
	float	angle;

	data = get_data();
	if (axis == 1)
	{
		rot = (t_vec){1, 0, 0};
		add_rot(&cam_r->x, &angle, sign, axis);
	}
	else if (axis == 2)
	{
		if (data->proj)
			rot = base->k;
		else
			rot = (t_vec){-base->k.x, -base->k.y, -base->k.z};
		add_rot(&cam_r->y, &angle, sign, axis);
	}
	else if (axis == 3)
	{
		rot = (t_vec){0, 0, 1};
		add_rot(&cam_r->z, &angle, sign, axis);
	}
	base->i = rotate_vector_by_quaternion(base->i, axis_angle_to_quaternion(angle, rot));
	base->j = rotate_vector_by_quaternion(base->j, axis_angle_to_quaternion(angle, rot));
	base->k = rotate_vector_by_quaternion(base->k, axis_angle_to_quaternion(angle, rot));
	orthonormalize_base(data, base);
	printf("Base is :\n\t{%f, %f, %f}\n\t{%f, %f, %f}\n\t{%f, %f, %f}\n",
		data->wld.base.i.x, data->wld.base.i.y, data->wld.base.i.z,
		data->wld.base.j.x, data->wld.base.j.y, data->wld.base.j.z,
		data->wld.base.k.x, data->wld.base.k.y, data->wld.base.k.z);
}
