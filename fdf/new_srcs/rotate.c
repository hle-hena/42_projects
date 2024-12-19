/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/19 19:31:14 by hle-hena         ###   ########.fr       */
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

/* void	do_rot_point(t_data *data)
{
	t_trig	vals;
	float	temp_x;
	float	temp_y;
	float	temp_z;

	base->ori.x = 0 - base->rot_cen.x;
	base->ori.y = 0 - base->rot_cen.y;
	base->ori.z = 0 - base->rot_cen.z;
	vals = (t_trig){sin(base->rot_y), cos(base->rot_y)};
	temp_x = base->ori.x * vals.cos
		+ base->ori.z * vals.sin;
	temp_z = base->ori.z * vals.cos
		- base->ori.x * vals.sin;
	base->ori.x = temp_x;
	base->ori.z = temp_z;
	vals = (t_trig){sin(base->rot_x), cos(base->rot_x)};
	temp_y = base->ori.y * vals.cos
		- base->ori.z * vals.sin;
	temp_z = base->ori.z * vals.cos
		+ base->ori.y * vals.sin;
	base->ori.y = temp_y;
	base->ori.z = temp_z;
	vals = (t_trig){sin(base->rot_z), cos(base->rot_z)};
	temp_x = base->ori.x * vals.cos
		- base->ori.y * vals.sin;
	temp_y = base->ori.y * vals.cos
		+ base->ori.x * vals.sin;
	base->ori.x = temp_x;
	base->ori.y = temp_y;
	base->ori.x += base->rot_cen.x;
	base->ori.y += base->rot_cen.y;
	base->ori.z += base->rot_cen.z;
	printf("point is\t%f\t%f\t%f\n", base->ori.x,
		base->ori.y,
		base->ori.z);
	base->ori = (t_vec){0, 0, 0};
} */

void	do_rot(t_base *base, t_vec rot)
{
	base->i = (t_vec){1, 0, 0};
	base->j = (t_vec){0, 1, 0};
	base->k = (t_vec){0, 0, -0.1};
	do_roty(base, (t_trig){sin(rot.y), cos(rot.y)});
	do_rotx(base, (t_trig){sin(rot.x), cos(rot.x)});
	do_rotz(base, (t_trig){sin(rot.z), cos(rot.z)});
	// do_rot_point(data);

	// printf("cen is\t%d\t%d\t%d\n", base->rot_cen.x, base->rot_cen.y, base->rot_cen.z);
	// Use the updated values of i, j, k to calculate transformed coordinates
	// Assuming `x`, `y`, and `z` are some point coordinates
/* 	float x = 1, y = 1, z = 1; // Example point
	float n_x = (x * base->i.x + y * base->j.x + z * base->k.x + base->ori.x);
	float n_y = (x * base->i.y + y * base->j.y + z * base->k.y + base->ori.y);
	float n_z = (x * base->i.z + y * base->j.z + z * base->k.z + base->ori.z);
	
	// Output transformed coordinates
	printf("Transformed point: n_x = %f, n_y = %f, n_z = %f\n", n_x, n_y, n_z); */
}