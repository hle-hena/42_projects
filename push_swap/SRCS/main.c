/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:29 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/14 19:44:13 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print(void *content)
{
	printf("[%d] --> ", *(int *)content);
}

int	main(int ac, char **av)
{
	t_list	**stack_a;
	t_list	**stack_b;
	int		*values;
	size_t	i;

	i = 0;
	stack_a = get_stack(0);
	stack_b = get_stack(1);
	values = ft_calloc(ac, sizeof(int));
	while (++i <= (size_t)ac - 1)
	{
		values[i - 1] = av[i][0] - '0';
		ft_lstadd_back(stack_a, ft_lstnew(&values[i - 1]));
	}
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("\nExecuting sa, result is '%d'\n", do_func("sa", stack_a, stack_b));
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	printf("\nExecuting pb, result is '%d'\n", do_func("pb", stack_a, stack_b));
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	printf("\nExecuting pa, result is '%d'\n", do_func("pa", stack_a, stack_b));
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	printf("\nExecuting ra, result is '%d'\n", do_func("ra", stack_a, stack_b));
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	printf("\nExecuting rra, result is '%d'\n", do_func("rra", stack_a, stack_b));
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	printf("\nExecuting rra, result is '%d'\n", do_func("rra", stack_a, stack_b));
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
}
