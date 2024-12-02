/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:04:40 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/02 15:48:41 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

int	main(int ac, char **av)
{
	t_list	**stack_a;
	t_list	**stack_b;
	t_push	nb_rot;
	int		size;
	int		min;

	get_values(ac, av);
	stack_a = get_stack(0);
	stack_b = get_stack(1);
	while (ft_lstsize(*stack_a) > 3 && ft_lstsize(*stack_b) < 2)
		do_func_print(get_cmds()[3]);
	while (ft_lstsize(*stack_a) > 3)
		calc_push(1, *get_stack(0), *get_stack(1), &is_smaller);
	push_sort_3();
	while (*get_stack(1))
		calc_push(0, *get_stack(1), *get_stack(0), &is_bigger);
	size = ft_lstsize(*get_stack(0));
	min = find_extrem(*get_stack(0), 0);
	nb_rot = (t_push){0};
	nb_rot.score_b = ft_tern_int(min <= (size / 2), min, -(size - min));
	do_push(nb_rot, 0);
	free_all();
}
