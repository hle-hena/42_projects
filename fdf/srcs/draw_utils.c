/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 11:18:25 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	img[point.y * data->win_wid + point.x] = color;
}

void	draw_high(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	float	percent;
	t_point	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dx) - dy;
	percent = 0;
	curr = (t_point){start.x, start.y, 0, (t_col){0}};
	while (curr.y <= end.y)
	{
		if (point_is_in_fov(data, curr))
			put_pixel(data, curr, calc_color(get_color(start, end, percent)));
		if (err > 0)
		{
			curr.x += ft_tern_int(dx < 0, -1, 1);
			err += 2 * (ft_abs(dx) - dy);
		}
		else
			err += 2 * ft_abs(dx);
		curr.y += 1;
		percent += (float)1 / dy;
	}
}

void	draw_low(t_data *data, t_point start, t_point end)
{
	int		dx;
	int		dy;
	int		err;
	float	percent;
	t_point	curr;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dy) - dx;
	percent = 0;
	curr = (t_point){start.x, start.y, 0, (t_col){0}};
	while (curr.x <= end.x)
	{
		if (point_is_in_fov(data, curr))
			put_pixel(data, curr, calc_color(get_color(start, end, percent)));
		if (err > 0)
		{
			curr.y += ft_tern_int(dy < 0, -1, 1);
			err += 2 * (ft_abs(dy) - dx);
		}
		else
			err += 2 * ft_abs(dy);
		curr.x += 1;
		percent += (float)1 / dx;
	}
}

	// printf("x is %d; y is %d; z is %d\n", x, y, z);
	// printf("\t\tn_x is %d; n_y is %d; n_z is %d\n\n", n_x, n_y, n_z);

/* int	color(t_point a, t_point b)
{
	return (0x00000000);
} */
