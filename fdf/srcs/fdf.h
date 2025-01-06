/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:28 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/06 16:36:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
#include <stdio.h>

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
	int	**color;
	int	len;
	int	wid;
	int	col;
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
	int		init_scale;
}	t_wld;

typedef	struct	s_events
{
	int	mo_f;
	int	mo_s;
	int	rot_x;
	int	rot_y;
	int	rot_z;
	int	sc;
}	t_event;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		proj;
	int		win_len;
	int		win_wid;
	t_event	event;
	t_obj	obj;
	t_wld	wld;
}	t_data;

/************************/
/*		main.c			*/
/************************/
t_data	*get_data(void);

/************************/
/*		mlx.c			*/
/************************/
int		event_loop(t_data *data);
int		key_press(int keycode, t_data *data);
int		key_down(int keycode, t_data *data);
int		mouse_down(int button, int x, int y, t_data *data);
int		mouse_up(int button, int x, int y, t_data *data);

/************************/
/*		mlx_utils.c		*/
/************************/
int		mlx_close(t_data *data);

/************************/
/*		movement.c		*/
/************************/
void	move_forward(t_data *data, int sign);
void	move_side(t_data *data, int sign);

/************************/
/*		draw.c			*/
/************************/
void	draw_map(t_data *data, int color);

/************************/
/*		draw_utils.c	*/
/************************/
void	put_pixel(t_data *data, t_point point, int color);
int		point_is_in_fov(t_data *data, t_point point);
void	draw_low(t_data *data, t_point start, t_point end);
void	draw_high(t_data *data, t_point start, t_point end);

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
void	go_to_proj(t_data *data);

/************************/
/*		point.c			*/
/************************/
t_vec	vec(t_obj obj, t_wld wld, t_point point);

/************************/
/*		color.c			*/
/************************/
t_col	get_real_color(t_obj obj, t_wld wld, t_vec curr);
t_col	get_grad(t_point start, t_point end, float percent);
void	set_color(t_obj *obj);
void	get_color(t_data *data, t_line *line, t_point start, t_point end);

/************************/
/*		color_utils.c	*/
/************************/
int		calc_color(t_col col);
t_col	rev_calc_color(int col);
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
void	do_rot(t_vec *cam_r, t_base *base, int sign, int axis);

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
void	parse_file(t_obj *obj, char *path);

/************************/
/*		parser_utils.c	*/
/************************/
int		line_size(char **line);
// void	find_extrem(int val, t_obj *obj);
void	extract_data(t_obj	*obj, char *data, int x, int y);
int		is_valid_arg(char *str);
void	get_matsize(t_mat *mat, int fd);

/************************/
/*		end.c			*/
/************************/
int		mlx_del(t_data *data);
void	ft_perror(int error_code, int clean, char *custom_mess);
void	ft_pend_prog(int clean, char *custom_mess);

#endif