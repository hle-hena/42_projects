/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:44:00 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/14 18:25:13 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sb(t_list **stack_b)
{
	// t_list	**stack_b;
	t_list	*temp;

	// stack_b = get_stack(1);
	if (!(*stack_b) || !(*stack_b)->next)
		return ;
	temp = *stack_b;
	*stack_b = (*stack_b)->next;
	temp->next = (*stack_b)->next;
	(*stack_b)->next = temp;
}

void	ft_pb(t_list **stack_b, t_list **stack_a)
{
	// t_list	**stack_a;
	// t_list	**stack_b;
	t_list	*temp;

	// stack_a = get_stack(0);
	// stack_b = get_stack(1);
	if (!(*stack_a))
		return ;
	temp = (*stack_a)->next;
	(*stack_a)->next = *stack_b;
	*stack_b = *stack_a;
	*stack_a = temp;
}

void	ft_rb(t_list **stack_b)
{
	// t_list	**stack_b;

	// stack_b = get_stack(1);
	if (!(*stack_b))
		return ;
	ft_lstadd_back(stack_b, *stack_b);
	*stack_b = (*stack_b)->next;
}

void	ft_rrb(t_list **stack_b)
{
	// t_list	**stack_b;
	t_list	*curr;
	t_list	*temp;

	// stack_b = get_stack(1);
	if (!(*stack_b))
		return ;
	temp = ft_lstlast(*stack_b);
	temp->next = *stack_b;
	curr = *stack_b;
	while (curr->next != temp)
		curr = curr->next;
	curr->next = NULL;
	*stack_b = temp;
}
