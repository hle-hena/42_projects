/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:29 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/15 17:32:51 by hle-hena         ###   ########.fr       */
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

int	ft_lstsorted(t_list *lst, int (*f)(t_list *))
{
	if (!lst)
		return (0);
	while (lst && lst->next)
	{
		if (f(lst))
			return (0);
		lst = lst->next;
	}
	return (1);
}

/*
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
*/
int	main(int ac, char **av)
{
	t_list	**stack_a;
	t_list	**stack_b;
	char	*func;
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
	printf("\n\n\n");
	printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	while (1)
	{
		if (ft_lstsorted(*stack_a, &is_increasing) && !(*stack_b))
			break ;
		func = init_tests();
		printf("\nExecuting the function [%s]\n\n", func);
		do_func(func, stack_a, stack_b);
		free(func);
		printf("Stack a : "); ft_lstiter(*stack_a, &print); printf("\n");
		printf("Stack b : "); ft_lstiter(*stack_b, &print); printf("\n");
	}
	free_tests(get_cmds());
	free(values);
	ft_lstclear(stack_a, NULL);
	ft_lstclear(stack_b, NULL);
	return (0);
}
