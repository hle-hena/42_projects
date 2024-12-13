/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:35:11 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/11 18:38:39 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_high(t_data *data, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	err;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dx) - dy;
	while (start.y != end.y)
	{
		mlx_pixel_put(data->mlx, data->win, start.x, start.y, color);
		if (err > 0)
		{
			start.x += ft_tern_int(dx < 0, -1, 1);
			err += 2 * (ft_abs(dx) - dy);
		}
		else
			err += 2 * ft_abs(dx);
		start.y += 1;
	}
}

void	draw_low(t_data *data, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	err;

	dx = end.x - start.x;
	dy = end.y - start.y;
	err = 2 * ft_abs(dy) - dx;
	while (start.x != end.x)
	{
		mlx_pixel_put(data->mlx, data->win, start.x, start.y, color);
		if (err > 0)
		{
			start.y += ft_tern_int(dy < 0, -1, 1);
			err += 2 * (ft_abs(dy) - dx);
		}
		else
			err += 2 * ft_abs(dy);
		start.x += 1;
	}
}

void	draw_line(t_data *data, t_point start, t_point end, int color)
{
	// if (color == 0)
	// 	color = color(start, end);
	if (ft_abs(end.y - start.y) < ft_abs(end.x - start.x))
	{
		if (start.x > end.x)
			return (draw_low(data, end, start, color));
		return (draw_low(data, start, end, color));
	}
	if (start.y > end.y)
		return (draw_high(data, end, start, color));
	return (draw_high(data, start, end, color));
}

/* void	draw_map(t_data *data)
{
	t_mat	mat;
	int		i;
	int		j;
	
	i = -1;
	mat = data->matrix;
	while (++i < mat.len - 1)
	{
		j = -1;
		while (++j < mat.wid)
		{
			if (i != mat.last - 2)
				draw_line(point(mat, i, j), point(mat, i + 1, j), 0);
			if (j != mat.wid - 1)
				draw_line(point(mat, i, j), point(mat, i, j + 1), 0);
		}
	}
} */