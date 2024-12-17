/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/17 16:16:36 by hle-hena         ###   ########.fr       */
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
	n_x = (x * data->disp.i.x + y * data->disp.j.x + z * data->disp.k.x + data->disp.ori.x)
		* data->disp.scale * 2 + data->disp.d_x * data->disp.scale * 2;
	n_y = (x * data->disp.i.y + y * data->disp.j.y + z * data->disp.k.y + data->disp.ori.y)
		* data->disp.scale * 2 + data->disp.d_y * data->disp.scale * 2;
	n_z = (x * data->disp.i.z + y * data->disp.j.z + z * data->disp.k.z + data->disp.ori.z)
		* data->disp.scale * 2;
	if (data->proj == 0)
		return (get_isometric(n_x, n_y));
	return ((t_point){n_x, n_y, n_z});
}

void	reset_img(t_data *data)
{
	draw_map(data, -1);
}

void	put_pixel(t_data *data, t_point point, int color)
{
	int	*img;
	int	temp;
	int	size_line;

	img = (int *)mlx_get_data_addr(data->img, &temp, &size_line, &temp);
	img[point.y * data->mat.wid * data->disp.init_scale * 3 + point.x] = color;
}

	// printf("x is %d; y is %d; z is %d\n", x, y, z);
	// printf("\t\tn_x is %d; n_y is %d; n_z is %d\n\n", n_x, n_y, n_z);

/* int	color(t_point a, t_point b)
{
	return (0x00000000);
} */
