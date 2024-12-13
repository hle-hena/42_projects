/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:58:28 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/11 14:37:51 by hle-hena         ###   ########.fr       */
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

typedef	struct s_matrix
{
	int	**matrix;
	int	len;
	int	wid;
}	t_mat;

typedef struct s_display
{
	int	rot_z;
	int	rot_y;
	int	scale;
}	t_disp;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_mat	matrix;
	t_disp	display;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/************************/
/*		main.c			*/
/************************/
int	mlx_del(t_data *data);

/************************/
/*		global.c		*/
/************************/
void	draw_line(t_data *data, t_point start, t_point end, int color);

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