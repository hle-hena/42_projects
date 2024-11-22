/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_res.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:41:20 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/22 16:20:57 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_s_res(t_list **stack, int witch)
{
	if (!witch)
		return (1000 / do_op((*stack)->next, *stack));
	return (1000 / do_op(*stack, (*stack)->next));
}

//might just set if push_b to always 0, not usefull, but not unusefull ?
int	ft_p_res(t_list *top, t_list *bot, t_list *push, int witch)
{
	if (!witch)
	{
		if (bot == top)
			return (1000);
		if (do_op(top, bot) > 0)
			return (1000 / do_op(push, bot) * ((do_op(push, top) > 0) * -1));
		return (1000 / do_op(bot, push) * ((do_op(push, bot) > 0) * -1));
	}
	return (0);
	if (bot == top)
		return (-1000);
	if (do_op(top, bot) > 0)
		return (-(1000 / do_op(push, bot) * ((do_op(push, top) > 0) * -1)));
	return (-(1000 / do_op(bot, push) * ((do_op(push, bot) > 0) * -1)));
}

/* int	ft_p_res(t_list *lst_top, t_list *lst_bot, t_list *lst_p, int witch)
{
	int	dist;
	int	res;

	if (lst_top == lst_bot)
		return (1000);
	dist = do_op(lst_bot, lst_top) + ft_tern_int(
			*(int *)lst_bot->content > *(int *)lst_top->content, 1, -1);
	res = (do_op(lst_p, lst_top) / dist) * 1000;
	if (!witch)
		return (res);
	if (res > 1000)
		return (res);
	else if (res < 0)
		return (-res - 1000);
	return (-res);
} */
/*
for pb

case 0 :
a -- 5 6 3
b -- 4

case 1 :
a -- 5 6 3
b -- 2

case 2 :
a -- 5 6 3
b -- 7

case 3 :
a -- 3 6 5
b -- 4

case 4 :
a -- 3 6 5
b -- 2

case 5 :
a -- 3 6 5
b -- 7

*/