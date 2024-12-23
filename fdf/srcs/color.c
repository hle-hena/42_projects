/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:16:47 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/23 15:58:30 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	round_to_n_places(float value, int n)
{
	float	factor;

	factor = pow(10, n);
	return (roundf(value * factor) / factor);
}

int	calc_color(t_col col)
{
	return ((col.re << 16) | (col.gr << 8) | col.bl);
}

t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr)
{
	float	percent;
	t_col	col1;
	t_col	col2;
	t_col	final;

	percent = (wld.cam.base.k.x * (curr.x - obj.wld_ori.x)
			+ wld.cam.base.k.y * (curr.y - obj.wld_ori.y)
			+ wld.cam.base.k.z * (curr.z - obj.wld_ori.z));

	// printf("%d\t%d\t%d\n", obj.max_h, obj.scale, wld.cam.scale * 2);
	// printf("%d\n", obj.max_h * obj.scale * wld.cam.scale * 2);
	// printf("%f, %f\n\n", percent, obj.max_h * obj.scale * wld.cam.scale * 2);
	// printf("Plane is %f\t%f\t%f\n", wld.cam.base.k.x, wld.cam.base.k.y, wld.cam.base.k.z);
	
	percent /= (obj.max_h * obj.scale * wld.cam.scale * 2);
	percent = round_to_n_places(percent, 6);
	
	// printf("%f\n", percent);

	if (percent <= 0.5 && percent >= 0)
	{
		col1 = (t_col){0xFF, 0xFF, 0xFF};
		col2 = (t_col){0xFF, 0xFB, 0x7D};
		percent /= 0.5;
	}
	else if (percent > 0.5)
	{
		col1 = (t_col){0xFF, 0xFB, 0x7D};
		col2 = (t_col){0xFF, 0x4B, 0xF3};
		percent = (percent - 0.5) / 0.5;
	}
	else
		return ((t_col){0, 0, 0});
	final = (t_col){col1.re + (col2.re - col1.re) * percent,
		col1.gr + (col2.gr - col1.gr) * percent,
		col1.bl + (col2.bl - col1.bl) * percent};
	return (final);
}

int	get_color(t_point start, t_point end, float percent)
{
	t_col	color;

	color.re = start.col.re + (end.col.re - start.col.re) * percent;
	color.gr = start.col.gr + (end.col.gr - start.col.gr) * percent;
	color.bl = start.col.bl + (end.col.bl - start.col.bl) * percent;
	// printf("percent is %f\n", percent);
	return (calc_color(color));
}
