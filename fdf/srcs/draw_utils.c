/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/01 16:46:21 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_img(t_data *data)
{
	draw_map(data, 0);
}

int	point_is_in_fov(t_data *data, t_point point)
{
	if (point.x < data->obj.mat.wid * data->wld.init_scale * 3 && point.x >= 0
		&& point.y < data->obj.mat.len * data->wld.init_scale * 3
		&& point.y >= 0)
		return (1);
	return (0);
}

void	put_pixel(t_data *data, t_point point, int color)
{
	int	*img;
	int	temp;
	int	size_line;

	img = (int *)mlx_get_data_addr(data->img, &temp, &size_line, &temp);
	img[point.y * data->obj.mat.wid * data->wld.init_scale * 3 + point.x] = color;
}

void	change_point(t_point *change, t_point other)
{
	float	param;
	t_point	n_point;

	param = (float)(1 - change->z) / (other.z - change->z);
	n_point = (t_point){change->x + param * (other.x - change->x),
		change->y + param * (other.y - change->y), 1, get_color(*change, other, param)};
	*change = n_point;
}

	// printf("x is %d; y is %d; z is %d\n", x, y, z);
	// printf("\t\tn_x is %d; n_y is %d; n_z is %d\n\n", n_x, n_y, n_z);

/* int	color(t_point a, t_point b)
{
	return (0x00000000);
} */
