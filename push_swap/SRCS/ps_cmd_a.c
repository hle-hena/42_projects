/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_cmd_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:30 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/14 18:18:57 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_sa(t_list **stack_a)
{
	// t_list	**stack_a;
	t_list	*temp;

	// stack_a = get_stack(0);
	if (!(*stack_a) || !(*stack_a)->next)
		return ;
	temp = *stack_a;
	*stack_a = (*stack_a)->next;
	temp->next = (*stack_a)->next;
	(*stack_a)->next = temp;
}

void	ft_pa(t_list **stack_a, t_list **stack_b)
{
	// t_list	**stack_a;
	// t_list	**stack_b;
	t_list	*temp;

	// stack_a = get_stack(0);
	// stack_b = get_stack(1);
	if (!(*stack_b))
		return ;
	temp = (*stack_b)->next;
	(*stack_b)->next = *stack_a;
	*stack_a = *stack_b;
	*stack_b = temp;
}

void	ft_ra(t_list **stack_a)
{
	// t_list	**stack_a;
	t_list	*temp;

	// stack_a = get_stack(0);
	if (!(*stack_a))
		return ;
	temp = *stack_a;
	ft_lstadd_back(stack_a, temp);
	*stack_a = temp->next;
	temp->next = NULL;
}

void	ft_rra(t_list **stack_a)
{
	// t_list	**stack_a;
	t_list	*curr;
	t_list	*temp;

	// stack_a = get_stack(0);
	if (!(*stack_a))
		return ;
	temp = ft_lstlast(*stack_a);
	temp->next = *stack_a;
	curr = *stack_a;
	while (curr->next != temp)
		curr = curr->next;
	curr->next = NULL;
	*stack_a = temp;
}
