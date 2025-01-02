/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:04:40 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/02 12:05:00 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_point(t_vec *change, t_vec other)
{
	float	param;
	t_vec	n_point;

	param = (float)(1 - change->z) / (other.z - change->z);
	n_point = (t_vec){change->x + param * (other.x - change->x),
		change->y + param * (other.y - change->y), 1};
	*change = n_point;
}
