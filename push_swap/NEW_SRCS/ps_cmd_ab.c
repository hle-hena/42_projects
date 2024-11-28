/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_ab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:51:02 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 10:45:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_sab(t_list **stack_a, t_list **stack_b)
{
	int	res;

	res = ft_s(stack_a, 0);
	res += ft_s(stack_b, 1);
	return (res);
}

int	ft_rab(t_list **stack_a, t_list **stack_b)
{
	int	diff;

	diff = ft_abs(do_op(*stack_a, *stack_b));
	ft_r(stack_a, stack_b, 1);
	ft_r(stack_b, stack_a, 1);
	return (1000 * (ft_abs(do_op(*stack_a, *stack_b)) - diff));
}

int	ft_rrab(t_list **stack_a, t_list **stack_b)
{
	int	diff;

	diff = ft_abs(do_op(*stack_a, *stack_b));
	ft_rr(stack_a, stack_b, 1);
	ft_rr(stack_b, stack_a, 1);
	return (1000 * (ft_abs(do_op(*stack_a, *stack_b)) - diff));
}
