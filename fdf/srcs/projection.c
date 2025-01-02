/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:58:00 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/02 12:44:41 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_iso(t_data *data, t_line *line, t_vec *start, t_vec *end)
{
	line->start = (t_point){start->x + (data->win_wid / 2),
		start->y + (data->win_len / 2), 0, (t_col){0, 0, 0}};
	line->end = (t_point){end->x + (data->win_wid / 2),
		end->y + (data->win_len / 2), 0, (t_col){0, 0, 0}};
	return (1);
}

int	get_persp(t_data *data, t_line *line, t_vec *start, t_vec *end)
{
	float fov_scale_x;
	float fov_scale_y;

    fov_scale_x = data->win_wid / (2.0f * tan(30 / 2.0f));
    fov_scale_y = data->win_len / (2.0f * tan(30 / 2.0f));
	if (start->z < 1 && end->z < 1)
		return (0);
	if (start->z < 1)
		change_point(start, *end);
	else if (end->z < 1)
		change_point(end, *start);
	line->start = (t_point){(start->x * fov_scale_x) / start->z + (data->win_wid / 2),
		(start->y * fov_scale_y) / start->z + (data->win_len / 2), 0, (t_col){0, 0, 0}};
	line->end = (t_point){(end->x * fov_scale_x) / end->z + (data->win_wid / 2),
		(end->y * fov_scale_y) / end->z + (data->win_len / 2), 0, (t_col){0, 0, 0}};
	// *start = (t_point){start->x + (data->win_wid / 2),
	// 	start->y + (data->win_len / 2), 0, start->col};
	// *end = (t_point){end->x + (data->win_wid / 2),
	// 	end->y + (data->win_len / 2), 0, end->col};
	return (1);
}

int	calc_point(t_data *data, t_line *line, t_vec *start, t_vec *end)
{
	if (data->proj == 0)
		return (get_iso(data, line, start, end));
	else if (data->proj == 1)
		return(get_persp(data, line, start, end));
	return (0);
}
