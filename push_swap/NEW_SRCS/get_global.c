/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:23:05 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/21 11:51:19 by hle-hena         ###   ########.fr       */
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

int	*get_values(int ac, char **av)
{
	static int	*values;
	
	if (!values)
		values = parse_imput(ac, av);
	if (!values)
		return (fall_back(), NULL);
	return (values);
}

t_list	**cpy_stack(int opt)
{
	t_list	*stack;
	t_list	**final;

	stack = ft_lstmap(*get_stack(opt), NULL, &ft_del);
	if (!stack)
		return (fall_back(), NULL);
	final = &stack;
	return (final);
}

t_list	**get_cpy(int opt)
{
	static t_list	**stack_a_cpy;
	static t_list	**stack_b_cpy;

	if (!stack_a_cpy)
		stack_a_cpy = cpy_stack(0);
	if (!stack_b_cpy)
		stack_b_cpy = cpy_stack(1);
	if (!opt)
		return (stack_a_cpy);
	return (stack_b_cpy);
}

char	**get_cmds(void)
{
	static char	*funcs[9] = {"sa", "sb", "pb", "pa", "ra", "rb", "rra", "rrb",
		/* "ss", "rr", "rrr", */ NULL};

	return (funcs);
}
