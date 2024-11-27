/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:23:05 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/27 17:14:19 by hle-hena         ###   ########.fr       */
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
		return (fall_back(NULL, NULL), NULL);
	return (values);
}

char	**get_cmds(void)
{
	static char	*funcs[9] = {"sa", "sb", "pa", "pb", "ra", "rb", "rra", "rrb",
		/* "ss", "rr", "rrr", */ NULL};

	return (funcs);
}

t_list	**get_states(int opt)
{
	static t_list	*states_a;
	static t_list	*states_b;

	if (!opt)
		return (states_a);
	return (states_b);
}