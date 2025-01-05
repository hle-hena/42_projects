/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:43:53 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 11:03:31 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calc_color(t_col col)
{
	return ((col.re << 16) | (col.gr << 8) | col.bl);
}

void	chose_color_2(t_col *col1, t_col *col2, float *percent)
{
	*percent *= -1;
	if (*percent <= 0.5)
	{
		*col1 = (t_col){0xFF, 0xFF, 0xFF};
		*col2 = (t_col){0x80, 0xFF, 0xBA};
		*percent *= 2;
	}
	else if (*percent > 0.5)
	{
		*col1 = (t_col){0x80, 0xFF, 0xBA};
		*col2 = (t_col){0x00, 0xF2, 0xFF};
		*percent = (*percent - 0.5) * 2;
	}
}

void	chose_color(t_col *col1, t_col *col2, float *percent)
{
	if (*percent >= 0)
	{
		if (*percent <= 0.5)
		{
			*col1 = (t_col){0xFF, 0xFF, 0xFF};
			*col2 = (t_col){0xFF, 0xFB, 0x7D};
			*percent *= 2;
		}
		else if (*percent > 0.5)
		{
			*col1 = (t_col){0xFF, 0xFB, 0x7D};
			*col2 = (t_col){0xFF, 0x4B, 0xF3};
			*percent = (*percent - 0.5) * 2;
		}
		return ;
	}
	chose_color_2(col1, col2, percent);
}
