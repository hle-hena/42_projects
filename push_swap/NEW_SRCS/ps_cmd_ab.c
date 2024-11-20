/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_ab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:51:02 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/20 14:23:25 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sab(t_list **stack_a, t_list **stack_b, int witch)
{
	ft_s(stack_a, witch);
	ft_s(stack_b, witch);
}

void	ft_rab(t_list **stack_a, t_list **stack_b, int witch)
{
	ft_r(stack_a, stack_b, witch);
	ft_r(stack_b, stack_a, witch);
}

void	ft_rrab(t_list **stack_a, t_list **stack_b, int witch)
{
	ft_rr(stack_a, stack_b, witch);
	ft_rr(stack_b, stack_a, witch);
}
