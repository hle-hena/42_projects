/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:52:48 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/02 14:56:53 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_s(t_list **stack)
{
	t_list	*temp;

	if (!(*stack))
		return ;
	if (!(*stack)->next)
		return ;
	temp = *stack;
	*stack = (*stack)->next;
	temp->next = (*stack)->next;
	(*stack)->next = temp;
}

void	ft_p(t_list **stack_to, t_list **stack_from)
{
	t_list	*temp;

	if (!(*stack_from))
		return ;
	temp = (*stack_from)->next;
	(*stack_from)->next = *stack_to;
	*stack_to = *stack_from;
	*stack_from = temp;
}

void	ft_r(t_list **stack)
{
	t_list	*temp;

	if (!(*stack))
		return ;
	if (!(*stack)->next)
		return ;
	temp = *stack;
	ft_lstadd_back(stack, temp);
	*stack = temp->next;
	temp->next = NULL;
}

void	ft_rr(t_list **stack)
{
	t_list	*curr;
	t_list	*temp;

	if (!(*stack))
		return ;
	temp = ft_lstlast(*stack);
	temp->next = *stack;
	curr = *stack;
	while (curr->next != temp)
		curr = curr->next;
	curr->next = NULL;
	*stack = temp;
}
