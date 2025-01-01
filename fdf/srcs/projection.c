/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:58:00 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/01 17:55:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_iso(t_data *data, t_point *start, t_point *end)
{
	*start = (t_point){start->x + (data->win_wid / 2),
		start->y + (data->win_len / 2), 0, start->col};
	*end = (t_point){end->x + (data->win_wid / 2),
		end->y + (data->win_len / 2), 0, end->col};
	return (1);
}

int	get_persp(t_data *data, t_point *start, t_point *end)
{
	if (start->z < 1 && end->z < 1)
		return (0);
	printf("A is {%d, %d, %d}\n", start->x, start->y, start->z);
	printf("B is {%d, %d, %d}\n", end->x, end->y, end->z);
	if (start->z < 1)
		change_point(start, *end);
	else if (end->z < 1)
		change_point(end, *start);
	printf("\tA is {%d, %d, %d}\n", start->x, start->y, start->z);
	printf("\tB is {%d, %d, %d}\n\n\n", end->x, end->y, end->z);
	*start = (t_point){(start->x) / start->z + (data->win_wid / 2),
		(start->y) / start->z + (data->win_len / 2),
		0, start->col};
	*end = (t_point){(end->x) / end->z + (data->win_wid / 2),
		(end->y) / end->z + (data->win_len / 2),
		0, end->col};
	// *start = (t_point){start->x + (data->win_wid / 2),
	// 	start->y + (data->win_len / 2), 0, start->col};
	// *end = (t_point){end->x + (data->win_wid / 2),
	// 	end->y + (data->win_len / 2), 0, end->col};
	return (1);
}

int	calc_point(t_data *data, t_point *start, t_point *end)
{
	if (data->proj == 0)
		return (get_iso(data, start, end));
	else if (data->proj == 1)
		return(get_persp(data, start, end));
	return (0);
}
