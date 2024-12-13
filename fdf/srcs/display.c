/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:01:14 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/13 13:44:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_isometric(t_vec *vector, t_trig vals)
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
	t_trig	vals;

	vals = (t_trig){sin(data->disp.rot_x), sin(data->disp.rot_y),
		sin(data->disp.rot_z), cos(data->disp.rot_x),
		cos(data->disp.rot_y), cos(data->disp.rot_z)};
	if (data->proj == 0)
	{
		calc_isometric(&data->disp.i, vals);
		calc_isometric(&data->disp.j, vals);
		calc_isometric(&data->disp.k, vals);
	}
}
