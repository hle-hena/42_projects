/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:28 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/03 19:54:49 by hle-hena         ###   ########.fr       */
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

typedef struct s_line
{
	t_point	start;
	t_point	end;
}	t_line;

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
	float	max_h;
	float	min_h;
}	t_obj;

typedef struct s_camera
{
	t_base	base;
	t_base	init;
	t_vec	ori;
	t_vec	r_ori;
	t_vec	rot;
	int		scale;
	float	n_plane;
	float	f_plane;
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
/*		movement.c		*/
/************************/
void	move(t_data *data, int keycode);

/************************/
/*		draw.c			*/
/************************/
void	draw_map(t_data *data, int color);

/************************/
/*		draw_utils.c	*/
/************************/
void	put_pixel(t_data *data, t_point point, int color);
int		point_is_in_fov(t_data *data, t_point point);

/************************/
/*		projection.c	*/
/************************/
int		calc_point(t_data *data, t_line *line, t_vec *start, t_vec *end);

/************************/
/*		projection_		*/
/*			utils.c		*/
/************************/
int		move_point(t_data *data, t_point *start, t_point *end);
void	change_point(t_vec *change, t_vec other, int z);

/************************/
/*		point.c			*/
/************************/
t_vec	vec(t_obj obj, t_wld wld, t_point point);

/************************/
/*		color.c			*/
/************************/
t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr);
t_col	get_color(t_point start, t_point end, float percent);
void	set_color(t_data *data, t_line *line, t_vec start, t_vec end);

/************************/
/*		color_utils.c	*/
/************************/
int		calc_color(t_col col);
void	chose_color(t_col *col1, t_col *col2, float *percent);

/************************/
/*		float.c			*/
/************************/
float	round_float(float value, int n);
void	round_vec(t_vec *vec);

/************************/
/*		rotate.c		*/
/************************/
void	look_at(t_base *base, t_base init, t_vec rot);
void	do_rot(t_vec *cam_r, t_base *base, int keycode);

/************************/
/*		rotate_utils.c	*/
/************************/
void	do_rot_yxz(t_vec *vec, t_trig rot_y, t_trig rot_x, t_trig rot_z);
void	do_rotx(t_base *base, t_trig vals);
void	do_roty(t_base *base, t_trig vals);
void	do_rotz(t_base *base, t_trig vals);
void	block_rot(float *val, float *rot, int axis);

/************************/
/*		init.c			*/
/************************/
void	init_data(t_data *data, char **path);

/************************/
/*		parser.c		*/
/************************/
void	parse_file(t_mat *mat, char *path, t_obj *obj);

/************************/
/*		end.c			*/
/************************/
int		mlx_del(t_data *data);
void	ft_perror(int error_code, int clean, char *custom_mess);
void	ft_pend_prog(int clean, char *custom_mess);

#endif