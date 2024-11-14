/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:55 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/14 19:43:58 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*get_nlast_element(t_list *stack, size_t n)
{
	size_t	stack_size;
	size_t	i;
	
	stack_size = ft_lstsize(stack);
	if (n + 1 >= stack_size)
		return (stack);
	i = 0;
	while (i < stack_size - n - 1 && stack)
	{
		stack = stack->next;
		i++;
	}
	return (stack);
}

t_list	*get_sample(t_list *o_stack)
{
	t_list	*new_stack;
	t_list	*temp;
	size_t	i;

	i = -1;
	new_stack = NULL;
	while (++i < FUTUR_SIGHT + 1 && o_stack)
	{
		temp = ft_lstnew(o_stack->content);
		//check if !temp
		//return ft_lstclear
		ft_lstadd_back(&new_stack, temp);
		o_stack = o_stack->next;
	}
	o_stack = get_nlast_element(o_stack, FUTUR_SIGHT);
	while (o_stack && i == FUTUR_SIGHT + 1)
	{
		temp = ft_lstnew(o_stack->content);
		//check if !temp
		//return ft_lstclear
		ft_lstadd_back(&new_stack, temp);
		o_stack = o_stack->next;
	}
	return (new_stack);
}

/* int	test(char **instructions)
{
	t_list	*sample_a;
	t_list	*sample_b;
	int		result;

	result = 0;
	sample_a = get_sample(*get_stack(0));
	sample_b = get_sample(*get_stack(1));
	while (*instructions)
	{
		result += 
	}
}

char	**init_tests()
{
	size_t	i;

	i = 0;
	while (i < FUTUR_SIGHT)
	{
		
	}
} */