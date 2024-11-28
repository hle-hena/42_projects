/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:58:06 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 15:59:41 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sab(void)
{
	ft_s(get_stack(0));
	ft_s(get_stack(1));
}

void	ft_rab(void)
{
	ft_r(get_stack(0));
	ft_r(get_stack(1));
}

void	ft_rrab(void)
{
	ft_rr(get_stack(0));
	ft_rr(get_stack(1));
}
