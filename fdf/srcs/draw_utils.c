/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/13 15:42:00 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_isometric(int x, int y)
{
	return ((t_point){x, y, 0});
}

t_point	point(t_data *data, int y, int x)
{
	int	n_x;
	int	n_y;
	int	n_z;
	int	z;

	z = data->mat.matrix[y][x];
	n_x = (x * data->disp.i.x + y * data->disp.j.x + z * data->disp.k.x)
			 * data->disp.scale + data->disp.scale * 0.5 * data->mat.wid;
	n_y = (x * data->disp.i.y + y * data->disp.j.y + z * data->disp.k.y)
			 * data->disp.scale + data->disp.scale * 0.1 * data->mat.len;
	n_z = (x * data->disp.i.z + y * data->disp.j.z + z * data->disp.k.z)
			 * data->disp.scale;
	// printf("x is %d; y is %d; z is %d\n", x, y, z);
	// printf("\t\tn_x is %d; n_y is %d; n_z is %d\n\n", n_x, n_y, n_z);
	if (data->proj == 0)
		return (get_isometric(n_x, n_y));
	return ((t_point){n_x, n_y, n_z});
}

/* int	color(t_point a, t_point b)
{
	return (0x00000000);
} */
