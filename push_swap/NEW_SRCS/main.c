/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:29 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/21 14:39:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print(void *content)
{
	printf("[%d] --> ", *(int *)content);
}

int	is_increasing(t_list *lst)
{
	return (do_op(lst, lst->next) > 0);
}

int	is_decreasing(t_list *lst)
{
	return (do_op(lst, lst->next) < 0);
}

int	main(int ac, char **av)
{
	t_list	**stack_a;
	t_list	**stack_b;
	char	*func;
	size_t	i;

	get_values(ac, av);
	stack_a = get_stack(0);
	stack_b = get_stack(1);
	// printf("Stack a : "); ft_lstiter(*get_stack(0), &print); printf("\n");
	// printf("Stack b : "); ft_lstiter(*get_stack(1), &print); printf("\n");
	i = -1;
	while (++i < 1)
	{
		if (ft_lstsorted(*stack_a, &is_increasing) && !(*stack_b))
			break ;
		func = get_cmds()[do_tests(0)];
		printf("\nExecuting the function [%s]\n\n", func);
		do_func(func, stack_a, stack_b);
	}
	free_all();
}
