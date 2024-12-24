/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:28 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/24 12:03:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
#include <stdio.h>

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEDOWN 4
# define ON_MOUSEUP 5
# define ON_MOUSEMOVE 6
# define ON_EXPOSE 12
# define ON_DESTROY 17

typedef struct s_trigometry_values
{
	float	sin;
	float	cos;
}	t_trig;

typedef struct s_color
{
	int	re;
	int	gr;
	int	bl;
}	t_col;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	t_col	col;
}	t_point;

typedef struct s_base
{
	t_vec	i;
	t_vec	j;
	t_vec	k;
}	t_base;

typedef struct s_matrix
{
	int	**matrix;
	int	len;
	int	wid;
}	t_mat;

typedef struct s_object
{
	t_base	base;
	t_base	init;
	t_vec	mat_ori;
	t_point	wld_ori;
	t_vec	r_ori;
	t_vec	rot;
	t_mat	mat;
	int		scale;
	float		max_h;
	float		min_h;
}	t_obj;

typedef struct s_camera
{
	t_base	base;
	t_base	init;
	t_vec	ori;
	t_vec	r_ori;
	t_vec	rot;
	int		scale;
	float	near_plane;
	float	far_plane;
}	t_cam;

typedef struct s_world
{
	t_base	base;
	t_base	init;
	t_cam	cam;
	// t_vec	normal;
	int		init_scale;
}	t_wld;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		proj;
	int		win_len;
	int		win_wid;
	t_obj	obj;
	t_wld	wld;
}	t_data;

/************************/
/*		main.c			*/
/************************/
t_data	*get_data(void);

/************************/
/*		draw.c			*/
/************************/
void	draw_map(t_data *data, int color);

/************************/
/*		draw_utils.c	*/
/************************/
void	reset_img(t_data *data);
int		pixel_is_in_fov(t_data *data, t_vec point);
void	put_pixel(t_data *data, t_point point, int color);

/************************/
/*		projection.c	*/
/************************/
t_point	point(t_obj obj, t_wld wld, t_point point, int color);
t_vec	calc_vec(t_obj obj, t_wld wld, t_point point);

/************************/
/*		color.c			*/
/************************/
t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr);
int		get_color(t_point start, t_point end, float percent);
int		calc_color(t_col col);

/************************/
/*		float.c			*/
/************************/
float	round_float(float value, int n);
void	round_vec(t_vec *vec);

/************************/
/*		display.c		*/
/************************/
void	calc_display(t_data *data);

/************************/
/*		rotate.c		*/
/************************/
void	do_rot(t_base *base, t_base init, t_vec rot);
// void	do_rotx(t_data *data, t_trig vals);
// void	do_roty(t_data *data, t_trig vals);
// void	do_rotz(t_data *data, t_trig vals);

/************************/
/*		init.c			*/
/************************/
void	init_data(t_data *data, char **path);

/************************/
/*		parser.c		*/
/************************/
void	parse_file(t_mat *mat, char *path, t_obj *obj);

/************************/
/*		errors.c		*/
/************************/
int		mlx_del(t_data *data);
void	ft_perror(int error_code, int clean, char *custom_mess);
void	ft_pend_prog(int clean, char *custom_mess);

#endif