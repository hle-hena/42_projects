/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:49:06 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/13 14:00:24 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_last_lines(int lines)
{
	int	i;

	i = 0;
	while (i++ < lines)
	{
		ft_printf("\033[1A");
		ft_printf("\033[K");
	}
}

char	*get_modif(t_data *data)
{
	if (data->modif.ind == 0)
		return ("fog");
	if (data->modif.ind == 1)
		return ("movement");
	if (data->modif.ind == 2)
		return ("rotation");
	if (data->modif.ind == 3)
		return ("fov");
	if (data->modif.ind == 4)
		return ("far plane");
	return (NULL);
}

int	get_modif_val(t_data *data)
{
	if (data->modif.ind == 0)
		return (data->modif.fog);
	if (data->modif.ind == 1)
		return (data->modif.mo_speed);
	if (data->modif.ind == 2)
		return (data->modif.rot_speed);
	if (data->modif.ind == 3)
		return (data->modif.fov);
	if (data->modif.ind == 4)
		return (data->modif.f_plane);
	return (0);
}

void	update_terminal_status(t_data *data, int init)
{
	if (!init)
		clear_last_lines(8);
	ft_printf("\033[0;36m/**********************************/\n");
	ft_printf("/*  FDF STATUS : RUNNING          */\n");
	ft_printf("/**********************************/\n");
	ft_printf("/* Current fps : %-3d              */\n", data->fps);
	ft_printf("/**********************************/\n");
	ft_printf("/* Current modifier : %-10s  */\n", get_modif(data));
	ft_printf("/*     value : %-15d    */\n", get_modif_val(data));
	ft_printf("/**********************************/\n\033[0;0m");
}
