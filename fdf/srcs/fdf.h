/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:28 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/16 11:52:50 by hle-hena         ###   ########.fr       */
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

typedef struct s_trigo_vals
{
	float	sin_x;
	float	sin_y;
	float	sin_z;
	float	cos_x;
	float	cos_y;
	float	cos_z;
}	t_trigs;

typedef struct s_trigo_val
{
	float	sin;
	float	cos;
}	t_trig;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_matrix
{
	int	**matrix;
	int	len;
	int	wid;
}	t_mat;

typedef struct s_display
{
	int		scale;
	float	rot_x;
	float	rot_y;
	float	rot_z;
	t_vec	i;
	t_vec	j;
	t_vec	k;
	int		d_x;
	int		d_y;
	int		d_z;
}	t_disp;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		proj;
	t_mat	mat;
	t_disp	disp;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

/************************/
/*		main.c			*/
/************************/
int		mlx_del(t_data *data);

/************************/
/*		draw.c			*/
/************************/
void	draw_line(t_data *data, t_point start, t_point end, int color);
void	draw_map(t_data *data);

/************************/
/*		draw_utils.c	*/
/************************/
t_point	point(t_data *data, int x, int y);

/************************/
/*		display.c		*/
/************************/
void	calc_display(t_data *data);

/************************/
/*		rotate.c		*/
/************************/
void	do_rotx(t_data *data, t_trig vals);
void	do_roty(t_data *data, t_trig vals);
void	do_rotz(t_data *data, t_trig vals);

/************************/
/*		init.c			*/
/************************/
void	init_data(t_data *data, char *path);

/************************/
/*		errors.c		*/
/************************/
void	ft_perror(int error_code, int clean, char *custom_mess);
void	ft_pend_prog(int clean, char *custom_mess);

#endif