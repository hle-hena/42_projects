/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_command_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:30 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/13 17:19:31 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	**get_stack(int opt)
{
	static t_list	*stack_a;
	static t_list	*stack_b;

	if (!opt)
		return (&stack_a);
	return (&stack_b);
}

void	ft_sa(void)
{
	t_list	**stack_a;
	t_list	*temp1;

	stack_a = get_stack(0);
	temp1 = *stack_a;
	*stack_a = (*stack_a)->next;
	temp1->next = (*stack_a)->next;
	(*stack_a)->next = temp1;
}

void	ft_sb(void)
{
	t_list	**stack_a;
	t_list	*temp1;

	stack_a = get_stack(0);
	temp1 = *stack_a;
	*stack_a = (*stack_a)->next;
	temp1->next = (*stack_a)->next;
	(*stack_a)->next = temp1;
}

void	ft_ss(void)
{
	ft_sa();
	ft_sb();
}

void	ft_pa(void)
{
	t_list	**stack_a;
	t_list	**stack_b;
	
	stack_a = get_stack(0);
	stack_b = get_stack(1);
}