/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:30 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/15 12:16:07 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_s(t_list **stack, int witch)
{
	t_list	*temp;

	if (!(*stack))
		return (0);
	if (!(*stack)->next)
		return (0);
	temp = *stack;
	*stack = (*stack)->next;
	temp->next = (*stack)->next;
	(*stack)->next = temp;
	if (!witch)
		return (do_op((*stack)->next, *stack));
	return (do_op(*stack, (*stack)->next));
}

int	ft_p(t_list **stack_to, t_list **stack_from, int witch)
{
	t_list	*temp;

	if (!(*stack_from))
		return (0);
	temp = (*stack_from)->next;
	(*stack_from)->next = *stack_to;
	*stack_to = *stack_from;
	*stack_from = temp;
	if (!witch)
		return (do_op((*stack_to)->next, *stack_to));
	return (do_op(*stack_to, (*stack_to)->next));
}

int	ft_r(t_list **stack, t_list **chk, int witch)
{
	t_list	*temp;
	t_list	*chk_closest_prev;
	t_list	*chk_closest_actu;
	t_list	*chk_last_stk;

	if (!(*stack))
		return (0);
	temp = *stack;
	ft_lstadd_back(stack, temp);
	*stack = temp->next;
	temp->next = NULL;
	if (witch)
	{
		chk_last_stk = ft_lstlast(*stack);
		chk_closest_prev = get_closest(chk_last_stk, *chk);
		chk_closest_actu = get_closest(*stack, *chk);
		return (do_op(chk_last_stk, chk_closest_prev)
			- do_op(*stack, chk_closest_actu));
	}
	return (0);
}

int	ft_rr(t_list **stack, t_list **chk, int witch)
{
	t_list	*curr;
	t_list	*temp;
	t_list	*chk_closest_prev;
	t_list	*chk_closest_actu;

	if (!(*stack))
		return (0);
	temp = ft_lstlast(*stack);
	temp->next = *stack;
	curr = *stack;
	while (curr->next != temp)
		curr = curr->next;
	curr->next = NULL;
	*stack = temp;
	if (witch)
	{
		chk_closest_prev = get_closest((*stack)->next, *chk);
		chk_closest_actu = get_closest(*stack, *chk);
		return (do_op((*stack)->next, chk_closest_prev)
			- do_op(*stack, chk_closest_actu));
	}
	return (0);
}
