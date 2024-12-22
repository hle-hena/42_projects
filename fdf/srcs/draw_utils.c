/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/22 15:09:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_projection(int x, int y, int z)
{
	t_data	*data;

	data = get_data();
	if (data->proj == 0)
	{
		if (z < data->wld.cam.near_plane)
			return((t_point){0, 0, 1});
		return ((t_point){x + (data->win_wid / 2),
			y + (data->win_len / 2), 0});
	}
	return ((t_point){x, y, z});
}

t_point	get_wld_coo(t_point point, t_obj obj, t_wld wld)
{
	t_point	centered;
	t_point	wld_coo;

	centered = (t_point){point.x - obj.mat_ori.x, point.y - obj.mat_ori.y,
		point.z - obj.mat_ori.z};
	wld_coo.x = (centered.x * obj.base.i.x + centered.y * obj.base.j.x
		+ centered.z * obj.base.k.x) * obj.scale * wld.cam.scale * 2;
	wld_coo.y = (centered.x * obj.base.i.y + centered.y * obj.base.j.y
		+ centered.z * obj.base.k.y) * obj.scale * wld.cam.scale * 2;
	wld_coo.z = (centered.x * obj.base.i.z + centered.y * obj.base.j.z
		+ centered.z * obj.base.k.z) * obj.scale * wld.cam.scale * 2;
	return ((t_point){wld_coo.x - obj.wld_ori.x, wld_coo.y - obj.wld_ori.y,
		wld_coo.z - obj.wld_ori.z});
}

t_point	point(t_obj obj, t_wld wld, int y, int x)
{
	t_point	wld_coo;
	t_vec	centered;
	t_vec	final;

	wld_coo = get_wld_coo((t_point){x, y, obj.mat.matrix[y][x]}, obj, wld);
	// printf("%d\t%d\t%d\n", 1, 1, 0);
	centered = (t_vec){wld_coo.x - wld.cam.ori.x, wld_coo.y - wld.cam.ori.y,
		wld_coo.z - wld.cam.ori.z};
	final.x = centered.x * wld.cam.base.i.x + centered.y * wld.cam.base.j.x
		+ centered.z * wld.cam.base.k.x;
	final.y = centered.x * wld.cam.base.i.y + centered.y * wld.cam.base.j.y
		+ centered.z * wld.cam.base.k.y;
	final.z = centered.x * wld.cam.base.i.z + centered.y * wld.cam.base.j.z
		+ centered.z * wld.cam.base.k.z;
	// printf("Becomes %f\t%f\t%f\n\n\n",
		// (1 - wld.cam.ori.x) * wld.cam.base.i.x + (1 - wld.cam.ori.y) * wld.cam.base.j.x,
		// (1 - wld.cam.ori.x) * wld.cam.base.i.y + (1 - wld.cam.ori.y) * wld.cam.base.j.y,
		// (1 - wld.cam.ori.x) * wld.cam.base.i.z + (1 - wld.cam.ori.y) * wld.cam.base.j.z);
	return (get_projection(final.x, final.y, final.z));
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
	img[point.y * data->obj.mat.wid * data->wld.init_scale * 3 + point.x] = color;
}

	// printf("x is %d; y is %d; z is %d\n", x, y, z);
	// printf("\t\tn_x is %d; n_y is %d; n_z is %d\n\n", n_x, n_y, n_z);

/* int	color(t_point a, t_point b)
{
	return (0x00000000);
} */
