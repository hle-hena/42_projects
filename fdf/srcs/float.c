/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:37:58 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 10:31:08 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	round_float(float value, int n)
{
	float	factor;

	factor = pow(10, n);
	return (roundf(value * factor) / factor);
}

void	round_vec(t_vec *vec)
{
	vec->x = round_float(vec->x, 5);
	vec->y = round_float(vec->y, 5);
	vec->z = round_float(vec->z, 5);
}