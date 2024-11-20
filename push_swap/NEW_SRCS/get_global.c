/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:23:05 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/20 16:53:28 by hle-hena         ###   ########.fr       */
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

t_list	**get_cpy(int opt)
{
	static t_list	**stack_a_cpy;
	static t_list	**stack_b_cpy;
	t_list			**stack_a;
	t_list			**stack_b;
	t_list			*node;

	stack_b = get_stack(1);
	if (!opt)
	{
		if (!stack_a_cpy)
			ft_lstmap(*stack_a, NULL, &ft_del);
		if (!stack_a_cpy)
			return (fall_back(), NULL);
		return (stack_a_cpy);
	}
	if (!stack_b_cpy)
		ft_lstmap(*stack_a, NULL, &ft_del);
	if (!stack_b_cpy)
		return (fall_back(), NULL);
	return (stack_b_cpy);
}

char	***get_cmds(void)
{
	static char	*funcs[9] = {"sa", "sb", "pb", "pa", "ra", "rb", "rra", "rrb",
		/* "ss", "rr", "rrr", */ NULL};
	static char	***tests;

	if (!tests)
		tests = create_tests(funcs);
	if (!tests)
		return (fall_back(), NULL);
	return (tests);
}
