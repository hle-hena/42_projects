/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/16 17:02:59 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	do_rotx(t_data *data, t_trig vals)
{
	float	temp_y;
	float	temp_z;

	temp_y = data->disp.i.y * vals.cos
		+ data->disp.i.z * vals.sin;
	temp_z = data->disp.i.z * vals.cos
		- data->disp.i.y * vals.sin;
	data->disp.i.y = temp_y;
	data->disp.i.z = temp_z;
	temp_y = data->disp.j.y * vals.cos
		+ data->disp.j.z * vals.sin;
	temp_z = data->disp.j.z * vals.cos
		- data->disp.j.y * vals.sin;
	data->disp.j.y = temp_y;
	data->disp.j.z = temp_z;
	temp_y = data->disp.k.y * vals.cos
		+ data->disp.k.z * vals.sin;
	temp_z = data->disp.k.z * vals.cos
		- data->disp.k.y * vals.sin;
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
		+ data->disp.i.y * vals.sin;
	temp_y = data->disp.i.y * vals.cos
		- data->disp.i.x * vals.sin;
	data->disp.i.x = temp_x;
	data->disp.i.y = temp_y;
	temp_x = data->disp.j.x * vals.cos
		+ data->disp.j.y * vals.sin;
	temp_y = data->disp.j.y * vals.cos
		- data->disp.j.x * vals.sin;
	data->disp.j.x = temp_x;
	data->disp.j.y = temp_y;
	temp_x = data->disp.k.x * vals.cos
		+ data->disp.k.y * vals.sin;
	temp_y = data->disp.k.y * vals.cos
		- data->disp.k.x * vals.sin;
	data->disp.k.x = temp_x;
	data->disp.k.y = temp_y;
}

void	do_rot(t_data *data)
{
	data->disp.i = (t_vec){1, 0, 0};
	data->disp.j = (t_vec){0, 0, 1};
	data->disp.k = (t_vec){0, -0.1, 0};
	do_roty(data, (t_trig){sin(data->disp.rot_y), cos(data->disp.rot_y)});
	do_rotx(data, (t_trig){sin(data->disp.rot_x), cos(data->disp.rot_x)});
	do_rotz(data, (t_trig){sin(data->disp.rot_z), cos(data->disp.rot_z)});
	// printf("i is \t%f; %f; %f\n", data->disp.i.x, data->disp.i.y, data->disp.i.z);
	// printf("j is \t%f; %f; %f\n", data->disp.j.x, data->disp.j.y, data->disp.j.z);
	// printf("k is \t%f; %f; %f\n", data->disp.k.x, data->disp.k.y, data->disp.k.z);
	// printf("rot is \t%f; %f; %f\n\n", data->disp.rot_x, data->disp.rot_y, data->disp.rot_z);
}
