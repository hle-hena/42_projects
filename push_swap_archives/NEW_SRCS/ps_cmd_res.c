/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:41:20 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 09:28:52 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_s_res(t_list **stack, int witch)
{
	if (!witch)
		return (1000 / do_op((*stack)->next, *stack));
	return (1000 / do_op(*stack, (*stack)->next));
}

int	ft_p_res(t_list *top, t_list *bot, t_list *push, int witch)
{
	if (!witch)
	{
		if (bot == top)
			return (50000);
		if (do_op(top, bot) > 0)
			return (5000 / do_op(push, bot) * ((do_op(push, top) > 0) * -1));
		return (5000 / do_op(bot, push) * ((do_op(push, bot) > 0) * -1));
	}
	// return (0);
	if (bot == top)
		return (-50000);
	if (do_op(top, bot) > 0)
		return (-(2000 / do_op(push, bot) * ((do_op(push, top) > 0) * -1)));
	return (-(2000 / do_op(bot, push) * ((do_op(push, bot) > 0) * -1)));
}


int	ft_r_res(t_list *stack, t_list *oth_stack)
{
	t_list	*last;
	int		diff_bef;
	int		diff_aft;

	if (!stack->next)
		return ((INT_MIN / FUTUR_SIGHT + 1) / 10);
	if (!stack->next->next)
		return ((INT_MIN / FUTUR_SIGHT + 1) / 10);
	last = ft_lstlast(stack);
	diff_bef = ft_abs(do_op(last, oth_stack));
	diff_aft = ft_abs(do_op(stack, oth_stack));
	if (diff_aft == diff_bef)
		return (0);
	return (1000 / (diff_bef - diff_aft));
}

int	ft_rr_res(t_list *stack, t_list *oth_stack)
{
	int	diff_bef;
	int	diff_aft;

	if (!stack->next)
		return ((INT_MIN / FUTUR_SIGHT + 1) / 10);
	if (!stack->next->next)
		return ((INT_MIN / FUTUR_SIGHT + 1) / 10);
	diff_bef = ft_abs(do_op(stack->next, oth_stack));
	diff_aft = ft_abs(do_op(stack, oth_stack));
	if (diff_aft == diff_bef)
		return (0);
	return (1000 / (diff_bef - diff_aft));
}

/*
for ra

case 0:
a : 4 2
b : 3
a : 2 4

case 1:
a : 3 1 2
b :

case 2:
a : 3 2 4
b : 1

case 3:
a : 

*/