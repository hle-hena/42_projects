/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 11:33:23 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/16 11:24:55 by hle-hena         ###   ########.fr       */
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
		- data->disp.i.z * vals.sin;
	temp_z = data->disp.i.z * vals.cos
		+ data->disp.i.x * vals.sin;
	data->disp.i.x = temp_x;
	data->disp.i.z = temp_z;
	temp_x = data->disp.j.x * vals.cos
		- data->disp.j.z * vals.sin;
	temp_z = data->disp.j.z * vals.cos
		+ data->disp.j.x * vals.sin;
	data->disp.j.x = temp_x;
	data->disp.j.z = temp_z;
	temp_x = data->disp.k.x * vals.cos
		- data->disp.k.z * vals.sin;
	temp_z = data->disp.k.z * vals.cos
		+ data->disp.k.x * vals.sin;
	data->disp.k.x = temp_x;
	data->disp.k.z = temp_z;
}

void	do_rotz(t_data *data, t_trig vals)
{
	float	temp_x;
	float	temp_y;

	temp_x = data->disp.i.y * vals.cos
		- data->disp.i.z * vals.sin;
	temp_y = data->disp.i.y * vals.sin
		+ data->disp.i.z * vals.cos;
	data->disp.i.x = temp_x;
	data->disp.i.y = temp_y;
	temp_x = data->disp.j.y * vals.cos
		- data->disp.j.z * vals.sin;
	temp_y = data->disp.j.y * vals.sin
		+ data->disp.j.z * vals.cos;
	data->disp.j.x = temp_x;
	data->disp.j.y = temp_y;
	temp_x = data->disp.k.y * vals.cos
		- data->disp.k.z * vals.sin;
	temp_y = data->disp.k.y * vals.sin
		+ data->disp.k.z * vals.cos;
	data->disp.k.x = temp_x;
	data->disp.k.y = temp_y;
}
