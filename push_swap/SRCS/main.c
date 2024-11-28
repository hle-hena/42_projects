/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:04:40 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 22:21:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

	// if (!lst)
	// 	return (0);
	// if (!lst->next)
	// 	return (0);
int	is_increasing(t_list *lst)
{
	return ((*(int *)lst->content - *(int *)lst->next->content) < 0);
}

static int	is_smaller(t_list *node_1, t_list *node_2)
{
	return (*(int *)node_1->content - *(int *)node_2->content);
}

static int	is_bigger(t_list *node_1, t_list *node_2)
{
	return (*(int *)node_2->content - *(int *)node_1->content);
}

/*
1 3 2		2 > 1	2 > 3	3 > 1
sa
ra

2 1 3		1 > 2	3 > 2	3 > 1
sa

2 3 1		2 > 1	3 > 2	3 > 1
rra

3 1 2	1 > 2
ra

3 2 1	1 > 2 -> sorted ?
sa	ra
rra	sa */

void	push_sort_3(void)
{
	t_list	*stack;

	stack = *get_stack(0);
	if (*(int *)stack->next->next->content > *(int *)stack->next->content
		&& *(int *)stack->next->content > *(int *)stack->content)
		return ;
	else if (*(int *)stack->content > *(int *)stack->next->content
		&& *(int *)stack->content > *(int *)stack->next->next->content)
	{
		do_func_print(get_cmds()[4]);
		if (!ft_lstsorted(*get_stack(0), &is_increasing))
			do_func_print(get_cmds()[0]);
	}
	else if (*(int *)stack->next->content > *(int *)stack->content
		&& *(int *)stack->next->next->content > *(int *)stack->content)
	{
		do_func_print(get_cmds()[6]);
		do_func_print(get_cmds()[0]);
	}
	else if (*(int *)stack->next->content > *(int *)stack->content
		&& *(int *)stack->next->content > *(int *)stack->next->next->content)
		do_func_print(get_cmds()[6]);
	else if (*(int *)stack->content > *(int *)stack->next->content
		&& *(int *)stack->next->next->content > *(int *)stack->next->content)
		do_func_print(get_cmds()[0]);
}

//5 3 4 2 1
int	main(int ac, char **av)
{
	t_list	**stack_a;
	t_list	**stack_b;
	char	buffer[10];

	get_values(ac, av);
	stack_a = get_stack(0);
	stack_b = get_stack(1);
	while (ft_lstsize(*stack_a) > 3 && ft_lstsize(*stack_b) < 3)
		do_func_print(get_cmds()[3]);
	while (ft_lstsize(*stack_a) > 3)
		calc_push(0, *get_stack(0), *get_stack(1), &is_smaller);
	push_sort_3();
	printf("Entering second part\n\n");
	while (*get_stack(1))
	{
		calc_push(0, *get_stack(1), *get_stack(0), &is_bigger);
		read(0, buffer, 1);
	}
	while (!(ft_lstsorted(*get_stack(0), &is_increasing)))
	{
		do_func_print(get_cmds()[4]);
		read(0, buffer, 1);
	}
	printf("%d - %d\n", !ft_lstsorted(*get_stack(0), &is_increasing), *get_stack(1) != NULL);
	printf("Stack a : "); ft_lstiter(*get_stack(0), &print); printf("\n");
	printf("Stack b : "); ft_lstiter(*get_stack(1), &print); printf("\n");
	free_all();
}
