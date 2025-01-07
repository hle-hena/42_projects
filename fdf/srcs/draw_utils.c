/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/07 12:44:46 by hle-hena         ###   ########.fr       */
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

void	calc_err(int *err, int *slope, int da, int db)
{
	if (*err > 0)
		{
			*slope += ft_tern_int(da < 0, -1, 1);
			*err += 2 * (ft_abs(da) - db);
		}
		else
			*err += 2 * ft_abs(da);
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
			put_pixel(data, curr, calc_color(get_grad(start, end, percent)));
		calc_err(&err, &curr.x, dx, dy);
		curr.y += 1;
		if (calc_color(start.col) != calc_color(end.col))
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
			put_pixel(data, curr, calc_color(get_grad(start, end, percent)));
		calc_err(&err, &curr.y, dy, dx);
		curr.x += 1;
		if (calc_color(start.col) != calc_color(end.col))
			percent += (float)1 / dx;
	}
}
