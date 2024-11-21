/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:41:20 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/21 19:09:08 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_s_res(t_list **stack, int witch)
{
	if (!witch)
		return (1000 / do_op((*stack)->next, *stack));
	return (1000 / do_op(*stack, (*stack)->next));
}

int	ft_p_res(t_list **stack_to, t_list **stack_from, int witch)
{
	int	dist;
	int	res;

	if (!witch)
	{
		dist = do_op(ft_lstlast(*stack_to), (*stack_to)->next);
		if (dist == 0)
			return (1000);
		res = (do_op(*stack_to, (*stack_to)->next) / dist) * 1000;
		if (res > 1000)
			return (-res + 999);
		return (res);
	}
	if (!*stack_from)
		return ((-2147483647 / (FUTUR_SIGHT * 2) + 1) / 10);
	dist = do_op(ft_lstlast(*stack_from), *stack_from);
	if (dist == 0)
		return (1);
	res = (do_op(*stack_to, *stack_from) / dist) * 1000;
	if (res > 1000)
		return (res);
	else if (res < 0)
		return (-res + 1000);
	return (-res);
}
