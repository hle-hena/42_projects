/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:30 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/25 16:00:38 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_s(t_list **stack, int witch)
{
	t_list	*temp;

	if (!(*stack))
		return ((-2147483647 / FUTUR_SIGHT + 1) / 10);
	if (!(*stack)->next)
		return ((-2147483647 / FUTUR_SIGHT + 1) / 10);
	temp = *stack;
	*stack = (*stack)->next;
	temp->next = (*stack)->next;
	(*stack)->next = temp;
	return (ft_s_res(stack, witch));
}

int	ft_p(t_list **stack_to, t_list **stack_from, int witch)
{
	t_list	*temp;
	int		res;

	if (!witch)
		res = ft_p_res(*stack_to, ft_lstlast(*stack_to), *stack_from, witch);
	if (!(*stack_from))
		return ((-2147483647 / FUTUR_SIGHT + 1) / 10);
	temp = (*stack_from)->next;
	(*stack_from)->next = *stack_to;
	*stack_to = *stack_from;
	*stack_from = temp;
	if (witch)
		res = ft_p_res(*stack_from, ft_lstlast(*stack_from), *stack_to, witch);
	return (res);
}

int	ft_r(t_list **stack, t_list **chk, int res)
{
	t_list	*temp;

	if (!(*stack))
		return ((-2147483647 / FUTUR_SIGHT + 1) / 10);
	if (!(*stack)->next)
		return ((-2147483647 / FUTUR_SIGHT + 1) / 10);
	temp = *stack;
	ft_lstadd_back(stack, temp);
	*stack = temp->next;
	temp->next = NULL;
	if (!res)
		return (ft_r_res(*stack, *chk));
	return (0);
}

int	ft_rr(t_list **stack, t_list **chk, int witch)
{
	t_list	*curr;
	t_list	*temp;

	if (!(*stack))
		return ((-2147483647 / FUTUR_SIGHT + 1) / 10);
	temp = ft_lstlast(*stack);
	temp->next = *stack;
	curr = *stack;
	while (curr->next != temp)
		curr = curr->next;
	curr->next = NULL;
	*stack = temp;
	if (!witch)
		return (ft_rr_res(*stack, *chk));
	return (0);
}
