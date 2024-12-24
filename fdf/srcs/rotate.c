/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/24 17:43:52 by hle-hena         ###   ########.fr       */
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

void	do_rot_yxz(t_vec *vec, t_trig rot_y, t_trig rot_x,
	t_trig rot_z)
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
}

void	do_rot(t_base *base, t_base init, t_vec rot)
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
	round_vec(&base->i);
	round_vec(&base->j);
	round_vec(&base->k);
}
