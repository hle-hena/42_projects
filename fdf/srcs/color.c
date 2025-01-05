/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:16:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 11:15:35 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr)
{
	float	percent;
	t_col	col1;
	t_col	col2;
	t_col	final;

	percent = (wld.base.k.x * (curr.x - obj.r_ori.x)
			+ wld.base.k.y * (curr.y - obj.r_ori.y)
			+ wld.base.k.z * (curr.z - obj.r_ori.z));
	if (percent > 0 && obj.max_h)
		percent /= (obj.max_h * obj.scale * wld.cam.scale * 2);
	else if (percent < 0 && obj.min_h)
		percent /= (obj.min_h * obj.scale * wld.cam.scale * -2);
	percent = round_float(percent, 5);
	chose_color(&col1, &col2, &percent);
	final = (t_col){col1.re + (col2.re - col1.re) * percent,
		col1.gr + (col2.gr - col1.gr) * percent,
		col1.bl + (col2.bl - col1.bl) * percent};
	return (final);
}

// if (calc_color(end.col) == 0x00FFFFFF && calc_color(start.col) != 0x00FFFFFF)
// 	col2 = (t_col){0xFF, 0xFB, 0x7D};
t_col	get_color(t_point start, t_point end, float percent)
{
	t_col	color;
	t_col	col1;
	t_col	col2;

	// return (start.col);
	if (percent < 0)
		return (start.col);
	col1 = (t_col){start.col.re, start.col.gr, start.col.bl};
	col2 = (t_col){end.col.re, end.col.gr, end.col.bl};
	color.re = col1.re + (col2.re - col1.re) * percent;
	color.gr = col1.gr + (col2.gr - col1.gr) * percent;
	color.bl = col1.bl + (col2.bl - col1.bl) * percent;
	return (color);
}

void	set_color(t_data *data, t_line *line, t_vec start, t_vec end)
{
	// line->start.col = (t_col){0xFF, 0xFF, 0xFF};
	// line->end.col = (t_col){0xFF, 0xFF, 0xFF};
	// return ;
	// //start here
	line->start.col = get_real_color(data->obj, data->wld, start);
	line->end.col = get_real_color(data->obj, data->wld, end);
}
