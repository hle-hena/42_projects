/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:22:35 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/20 16:52:39 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	get_projection(int x, int y, int z)
{
	t_data	*data;

	data = get_data();
	if (data->proj == 0)
	{
		return ((t_point){x + (data->win_wid / 2),
			y + (data->win_len / 2), 0});
	}
	return ((t_point){x, y, z});
}

t_point	get_wld_coo(t_point point, t_obj obj, t_disp disp)
{
	int	n_x;
	int	n_y;
	int	n_z;

	n_x = ((point.x - obj.ori.x) * obj.base.i.x
		+ (point.y - obj.ori.y) * obj.base.j.x
		+ (point.z - obj.ori.z) * obj.base.k.x)
		* obj.scale * disp.scale * 2;
	n_y = ((point.x - obj.ori.x) * obj.base.i.y
		+ (point.y - obj.ori.y) * obj.base.j.y
		+ (point.z - obj.ori.z) * obj.base.k.y)
		* obj.scale * disp.scale * 2;
	n_z = ((point.x - obj.ori.x) * obj.base.i.z
		+ (point.y - obj.ori.y) * obj.base.j.z
		+ (point.z - obj.ori.z) * obj.base.k.z)
		* obj.scale * disp.scale * 2;
	return ((t_point){n_x, n_y, n_z});
}

t_point	point(t_obj obj, t_disp disp, int y, int x)
{
	int		n_x;
	int		n_y;
	int		n_z;
	t_point	wld_coo;

	// z = obj.mat.matrix[y][x];
	// n_x = (((x - obj.ori.x) * obj.base.i.x * obj.scale * disp.scale * 2)
	// 		* disp.base.i.x
	// 	+ ((y - obj.ori.y) * obj.base.j.x * obj.scale * disp.scale * 2)
	// 		* disp.base.j.x
	// 	+ ((z - obj.ori.z) * obj.base.k.x * obj.scale * disp.scale * 2)
	// 		* disp.base.k.x);
	// n_y = (((x - obj.ori.x) * obj.base.i.y * obj.scale * disp.scale * 2
	// 		- disp.cam.ori.x) * disp.base.i.y
	// 	+ ((y - obj.ori.y) * obj.base.j.y * obj.scale * disp.scale * 2
	// 		- disp.cam.ori.y) * disp.base.j.y
	// 	+ ((z - obj.ori.z) * obj.base.k.y * obj.scale * disp.scale * 2
	// 		- disp.cam.ori.z) * disp.base.k.y);
	// n_z = (((x - obj.ori.x) * obj.base.i.z * obj.scale * disp.scale * 2
	// 		- disp.cam.ori.x) * disp.base.i.z
	// 	+ ((y - obj.ori.y) * obj.base.j.z * obj.scale * disp.scale * 2
	// 		- disp.cam.ori.y) * disp.base.j.z
	// 	+ ((z - obj.ori.z) * obj.base.k.z * obj.scale * disp.scale * 2
	// 		- disp.cam.ori.z) * disp.base.k.z);
	// return (get_projection(n_x, n_y, n_z));
	//Note that this version doesnt support rotation of the local object.
	// It does however support the rotation of the camera
	//Doesnt rotate properly either ...
	wld_coo = get_wld_coo((t_point){x, y, obj.mat.matrix[y][x]}, obj, disp);
	n_x = wld_coo.x * disp.base.i.x + wld_coo.y * disp.base.j.x
		+ wld_coo.z * disp.base.k.x - disp.cam.ori.x;
	n_y = wld_coo.x * disp.base.i.y + wld_coo.y * disp.base.j.y
		+ wld_coo.z * disp.base.k.y - disp.cam.ori.y;
	n_z = wld_coo.x * disp.base.i.z + wld_coo.y * disp.base.j.z
		+ wld_coo.z * disp.base.k.z - disp.cam.ori.z;
	// if (data->proj == 0)
	// 	return (get_isometric(n_x, n_y));
	return (get_projection(n_x, n_y, n_z));
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
	img[point.y * data->obj.mat.wid * data->disp.init_scale * 3 + point.x] = color;
}

	// printf("x is %d; y is %d; z is %d\n", x, y, z);
	// printf("\t\tn_x is %d; n_y is %d; n_z is %d\n\n", n_x, n_y, n_z);

/* int	color(t_point a, t_point b)
{
	return (0x00000000);
} */
