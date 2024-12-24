/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:16:47 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/24 17:44:30 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calc_color(t_col col)
{
	return ((col.re << 16) | (col.gr << 8) | col.bl);
}

void	chose_color_2(t_col *col1, t_col *col2, float *percent)
{
	*percent *= -1;
	if (*percent <= 0.5)
	{
		*col1 = (t_col){0xFF, 0xFF, 0xFF};
		*col2 = (t_col){0x80, 0xFF, 0xBA};
		*percent /= 0.5;
	}
	else if (*percent > 0.5)
	{
		*col1 = (t_col){0x80, 0xFF, 0xBA};
		*col2 = (t_col){0x00, 0xF2, 0xFF};
		*percent = (*percent - 0.5) / 0.5;
	}
}

void	chose_color(t_col *col1, t_col *col2, float *percent)
{
	if (*percent >= 0)
	{
		if (*percent <= 0.5)
		{
			*col1 = (t_col){0xFF, 0xFF, 0xFF};
			*col2 = (t_col){0xFF, 0xFB, 0x7D};
			*percent /= 0.5;
		}
		else if (*percent > 0.5)
		{
			*col1 = (t_col){0xFF, 0xFB, 0x7D};
			*col2 = (t_col){0xFF, 0x4B, 0xF3};
			*percent = (*percent - 0.5) / 0.5;
		}
		return ;
	}
	chose_color_2(col1, col2, percent);
}

t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr)
{
	float	percent;
	t_col	col1;
	t_col	col2;
	t_col	final;

	percent = (wld.cam.base.k.x * (curr.x - obj.r_ori.x)
			+ wld.cam.base.k.y * (curr.y - obj.r_ori.y)
			+ wld.cam.base.k.z * (curr.z - obj.r_ori.z));
	percent = round_float(percent, 3);
	if (percent >= 0)
	{
		if (obj.max_h)
			percent /= (obj.max_h * obj.scale * wld.cam.scale * 2);
	}
	else
		percent = percent / (obj.min_h * obj.scale * wld.cam.scale * 2 * -1);
	percent = round_float(percent, 3);
	chose_color(&col1, &col2, &percent);
	final = (t_col){col1.re + (col2.re - col1.re) * percent,
		col1.gr + (col2.gr - col1.gr) * percent,
		col1.bl + (col2.bl - col1.bl) * percent};
	return (final);
}

int	get_color(t_point start, t_point end, float percent)
{
	t_col	color;
	t_col	col1;
	t_col	col2;

	col1 = (t_col){start.col.re, start.col.gr, start.col.bl};
	// if (calc_color(start.col) == 0x00FFFFFF && calc_color(end.col) != 0x00FFFFFF)
	// 	col1 = (t_col){0xFF, 0xFB, 0x7D};
	col2 = (t_col){end.col.re, end.col.gr, end.col.bl};
	// if (calc_color(end.col) == 0x00FFFFFF && calc_color(start.col) != 0x00FFFFFF)
	// 	col2 = (t_col){0xFF, 0xFB, 0x7D};
	color.re = col1.re + (col2.re - col1.re) * percent;
	color.gr = col1.gr + (col2.gr - col1.gr) * percent;
	color.bl = col1.bl + (col2.bl - col1.bl) * percent;
	// printf("percent is %f\n", percent);
	return (calc_color(color));
}
