/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/17 16:43:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_rotx(t_data *data, t_trig vals)
{
	float	temp_y;
	float	temp_z;

	temp_y = data->disp.i.y * vals.cos
		- data->disp.i.z * vals.sin;
	temp_z = data->disp.i.z * vals.cos
		+ data->disp.i.y * vals.sin;
	data->disp.i.y = temp_y;
	data->disp.i.z = temp_z;
	temp_y = data->disp.j.y * vals.cos
		- data->disp.j.z * vals.sin;
	temp_z = data->disp.j.z * vals.cos
		+ data->disp.j.y * vals.sin;
	data->disp.j.y = temp_y;
	data->disp.j.z = temp_z;
	temp_y = data->disp.k.y * vals.cos
		- data->disp.k.z * vals.sin;
	temp_z = data->disp.k.z * vals.cos
		+ data->disp.k.y * vals.sin;
	data->disp.k.y = temp_y;
	data->disp.k.z = temp_z;
}

void	do_roty(t_data *data, t_trig vals)
{
	float	temp_x;
	float	temp_z;

	temp_x = data->disp.i.x * vals.cos
		+ data->disp.i.z * vals.sin;
	temp_z = data->disp.i.z * vals.cos
		- data->disp.i.x * vals.sin;
	data->disp.i.x = temp_x;
	data->disp.i.z = temp_z;
	temp_x = data->disp.j.x * vals.cos
		+ data->disp.j.z * vals.sin;
	temp_z = data->disp.j.z * vals.cos
		- data->disp.j.x * vals.sin;
	data->disp.j.x = temp_x;
	data->disp.j.z = temp_z;
	temp_x = data->disp.k.x * vals.cos
		+ data->disp.k.z * vals.sin;
	temp_z = data->disp.k.z * vals.cos
		- data->disp.k.x * vals.sin;
	data->disp.k.x = temp_x;
	data->disp.k.z = temp_z;
}

void	do_rotz(t_data *data, t_trig vals)
{
	float	temp_x;
	float	temp_y;

	temp_x = data->disp.i.x * vals.cos
		- data->disp.i.y * vals.sin;
	temp_y = data->disp.i.y * vals.cos
		+ data->disp.i.x * vals.sin;
	data->disp.i.x = temp_x;
	data->disp.i.y = temp_y;
	temp_x = data->disp.j.x * vals.cos
		- data->disp.j.y * vals.sin;
	temp_y = data->disp.j.y * vals.cos
		+ data->disp.j.x * vals.sin;
	data->disp.j.x = temp_x;
	data->disp.j.y = temp_y;
	temp_x = data->disp.k.x * vals.cos
		- data->disp.k.y * vals.sin;
	temp_y = data->disp.k.y * vals.cos
		+ data->disp.k.x * vals.sin;
	data->disp.k.x = temp_x;
	data->disp.k.y = temp_y;
}

void	do_rot_point(t_data *data)
{
	t_trig	vals;
	float	temp_x;
	float	temp_y;
	float	temp_z;

	data->disp.ori.x = -data->disp.rot_cen.x;
	data->disp.ori.y = -data->disp.rot_cen.y;
	data->disp.ori.z = -data->disp.rot_cen.z;
	vals = (t_trig){sin(data->disp.rot_y), cos(data->disp.rot_y)};
	temp_x = data->disp.ori.x * vals.cos
		+ data->disp.ori.z * vals.sin;
	temp_z = data->disp.ori.z * vals.cos
		- data->disp.ori.x * vals.sin;
	data->disp.ori.x = temp_x;
	data->disp.ori.z = temp_z;
	vals = (t_trig){sin(data->disp.rot_x), cos(data->disp.rot_x)};
	temp_y = data->disp.ori.y * vals.cos
		- data->disp.ori.z * vals.sin;
	temp_z = data->disp.ori.z * vals.cos
		+ data->disp.ori.y * vals.sin;
	data->disp.ori.y = temp_y;
	data->disp.ori.z = temp_z;
	vals = (t_trig){sin(data->disp.rot_z), cos(data->disp.rot_z)};
	temp_x = data->disp.ori.x * vals.cos
		- data->disp.ori.y * vals.sin;
	temp_y = data->disp.ori.y * vals.cos
		+ data->disp.ori.x * vals.sin;
	data->disp.ori.x = temp_x;
	data->disp.ori.y = temp_y;
	data->disp.ori.x += data->disp.rot_cen.x;
	data->disp.ori.y += data->disp.rot_cen.y;
	data->disp.ori.z += data->disp.rot_cen.z;
	printf("point is\t%f\t%f\t%f\n", data->disp.ori.x,
		data->disp.ori.y,
		data->disp.ori.z);
}

void	do_rot(t_data *data)
{
	data->disp.i = (t_vec){1, 0, 0};
	data->disp.j = (t_vec){0, 0, -1};
	data->disp.k = (t_vec){0, -0.1, 0};
	do_roty(data, (t_trig){sin(data->disp.rot_y), cos(data->disp.rot_y)});
	do_rotx(data, (t_trig){sin(data->disp.rot_x), cos(data->disp.rot_x)});
	do_rotz(data, (t_trig){sin(data->disp.rot_z), cos(data->disp.rot_z)});
	do_rot_point(data);
	

	// printf("cen is\t%d\t%d\t%d\n", data->disp.rot_cen.x, data->disp.rot_cen.y, data->disp.rot_cen.z);
	// Use the updated values of i, j, k to calculate transformed coordinates
	// Assuming `x`, `y`, and `z` are some point coordinates
/* 	float x = 1, y = 1, z = 1; // Example point
	float n_x = (x * data->disp.i.x + y * data->disp.j.x + z * data->disp.k.x + data->disp.ori.x);
	float n_y = (x * data->disp.i.y + y * data->disp.j.y + z * data->disp.k.y + data->disp.ori.y);
	float n_z = (x * data->disp.i.z + y * data->disp.j.z + z * data->disp.k.z + data->disp.ori.z);
	
	// Output transformed coordinates
	printf("Transformed point: n_x = %f, n_y = %f, n_z = %f\n", n_x, n_y, n_z); */
}