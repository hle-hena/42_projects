/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:16:47 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/08 13:53:02 by hle-hena         ###   ########.fr       */
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

void	set_color(t_obj *obj)
{
	int		i;
	int		j;
	t_col	col1;
	t_col	col2;
	float	percent;

	if (obj->mat.col)
		return ;
	i = -1;
	while (++i < obj->mat.len)
	{
		j = -1;
		while (++j < obj->mat.wid)
		{
			percent = (float)obj->mat.matrix[i][j];
			if (percent > 0 && obj->max_h)
				percent /= (obj->max_h);
			else if (percent < 0 && obj->min_h)
				percent /= (-obj->min_h);
			chose_color(&col1, &col2, &percent);
			obj->mat.color[i][j] = calc_color((t_col){col1.re + (col2.re
						- col1.re) * percent, col1.gr + (col2.gr - col1.gr)
					* percent, col1.bl + (col2.bl - col1.bl) * percent});
		}
	}
}

t_col	get_grad(t_col start, t_col end, float percent)
{
	t_col	color;
	t_col	col1;
	t_col	col2;

	if (percent <= 0)
		return (start);
	col1 = (t_col){start.re, start.gr, start.bl};
	col2 = (t_col){end.re, end.gr, end.bl};
	color.re = col1.re + (col2.re - col1.re) * percent;
	color.gr = col1.gr + (col2.gr - col1.gr) * percent;
	color.bl = col1.bl + (col2.bl - col1.bl) * percent;
	return (color);
}

//set power to 4 for visibility, set to 0.25 for night/horror view
void	get_color(t_data *data, t_line *line, t_point start, t_point end)
{
	float	percent;

	if (!data->proj)
	{
		line->start.col = rev_calc_color(data->obj.mat.color[start.y][start.x]);
		line->end.col = rev_calc_color(data->obj.mat.color[end.y][end.x]);
	}
	else
	{
		percent = pow((float)line->start.z / data->wld.cam.f_plane, 4);
		line->start.col = get_grad(rev_calc_color(data->obj.mat.color[start.y][start.x]), (t_col){0x00, 0x00, 0x00}, percent);
		percent = pow((float)line->end.z / data->wld.cam.f_plane, 4);
		line->end.col = get_grad(rev_calc_color(data->obj.mat.color[end.y][end.x]), (t_col){0x00, 0x00, 0x00}, percent);
	}
}
