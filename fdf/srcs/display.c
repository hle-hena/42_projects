/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:01:14 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/16 11:37:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_isometric(t_vec *vector, t_trigs vals)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = vector->x * vals.cos_y - vector->z * vals.sin_y;
	temp_y = vector->x * vals.sin_x * vals.sin_y + vector->y
		* vals.cos_x + vector->z * vals.cos_y * vals.sin_x;
	temp_z = vector->x * vals.cos_x * vals.sin_y - vector->y
		* vals.sin_x + vector->z * vals.cos_x * vals.cos_y;
	vector->x = temp_x;
	vector->y = temp_y;
	vector->z = temp_z;
}

void	calc_display(t_data *data)
{
	if (data->proj == 0)
	{
		do_roty(data, (t_trig){sin(data->disp.rot_y), cos(data->disp.rot_y)});
		do_rotx(data, (t_trig){sin(data->disp.rot_x), cos(data->disp.rot_x)});
	}
}
