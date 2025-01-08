/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:25:20 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/08 16:12:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_rotx(t_base *base, t_trig vals)
{
	float	temp_y;
	float	temp_z;

	temp_y = base->i.y * vals.cos
		- base->i.z * vals.sin;
	temp_z = base->i.z * vals.cos
		+ base->i.y * vals.sin;
	base->i.y = temp_y;
	base->i.z = temp_z;
	temp_y = base->j.y * vals.cos
		- base->j.z * vals.sin;
	temp_z = base->j.z * vals.cos
		+ base->j.y * vals.sin;
	base->j.y = temp_y;
	base->j.z = temp_z;
	temp_y = base->k.y * vals.cos
		- base->k.z * vals.sin;
	temp_z = base->k.z * vals.cos
		+ base->k.y * vals.sin;
	base->k.y = temp_y;
	base->k.z = temp_z;
}

void	do_roty(t_base *base, t_trig vals)
{
	float	temp_x;
	float	temp_z;

	temp_x = base->i.x * vals.cos
		+ base->i.z * vals.sin;
	temp_z = base->i.z * vals.cos
		- base->i.x * vals.sin;
	base->i.x = temp_x;
	base->i.z = temp_z;
	temp_x = base->j.x * vals.cos
		+ base->j.z * vals.sin;
	temp_z = base->j.z * vals.cos
		- base->j.x * vals.sin;
	base->j.x = temp_x;
	base->j.z = temp_z;
	temp_x = base->k.x * vals.cos
		+ base->k.z * vals.sin;
	temp_z = base->k.z * vals.cos
		- base->k.x * vals.sin;
	base->k.x = temp_x;
	base->k.z = temp_z;
}

void	do_rotz(t_base *base, t_trig vals)
{
	float	temp_x;
	float	temp_y;

	temp_x = base->i.x * vals.cos
		- base->i.y * vals.sin;
	temp_y = base->i.y * vals.cos
		+ base->i.x * vals.sin;
	base->i.x = temp_x;
	base->i.y = temp_y;
	temp_x = base->j.x * vals.cos
		- base->j.y * vals.sin;
	temp_y = base->j.y * vals.cos
		+ base->j.x * vals.sin;
	base->j.x = temp_x;
	base->j.y = temp_y;
	temp_x = base->k.x * vals.cos
		- base->k.y * vals.sin;
	temp_y = base->k.y * vals.cos
		+ base->k.x * vals.sin;
	base->k.x = temp_x;
	base->k.y = temp_y;
}

void	do_rot_yxz(t_vec *vec, t_trig rot_y, t_trig rot_x, t_trig rot_z)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = vec->x * (rot_y.cos * rot_z.cos)
		+ vec->y * (rot_x.sin * rot_y.sin * rot_z.cos - rot_x.cos * rot_z.sin)
		+ vec->z * (rot_x.cos * rot_y.sin * rot_z.cos + rot_x.sin * rot_z.sin);
	temp_y = vec->x * (rot_y.cos * rot_z.sin)
		+ vec->y * (rot_x.sin * rot_y.sin * rot_z.sin + rot_x.cos * rot_z.cos)
		+ vec->z * (rot_x.cos * rot_y.sin * rot_z.sin - rot_x.sin * rot_z.cos);
	temp_z = vec->x * (-rot_y.sin)
		+ vec->y * (rot_x.sin * rot_y.cos)
		+ vec->z * (rot_x.cos * rot_y.cos);
	vec->x = temp_x;
	vec->y = temp_y;
	vec->z = temp_z;
	round_vec(vec);
}

void	block_rot(float *val, float *rot, int axis)
{
	if (axis == 1 && ((180 * *val) / M_PI) >= 180)
	{
		*val = 180 * (M_PI / 180);
		*rot = 0;
	}
	else if (axis == 1 && ((180 * *val) / M_PI) <= 0)
	{
		*val = 0;
		*rot = 0;
	}
}
