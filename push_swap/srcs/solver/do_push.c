/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:09:58 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/20 12:25:16 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	find_extrem(t_list *stack, int opt)
{
	int	extrem_val;
	int	extrem_ind;
	int	i;

	i = 0;
	extrem_ind = 0;
	extrem_val = *(int *)stack->content;
	while (stack)
	{
		if (ft_tern_int(opt, *(int *)stack->content > extrem_val
				, *(int *)stack->content < extrem_val))
		{
			extrem_ind = i;
			extrem_val = *(int *)stack->content;
		}
		i++;
		stack = stack->next;
	}
	return (extrem_ind);
}

int	calc_score(t_list *node, t_list *stack, int (*f)(t_list *, t_list *),
				int extrem_ind)
{
	int		close_val;
	int		close_ind;
	int		res;
	int		i;

	close_val = f(node, stack);
	close_ind = 0;
	i = 0;
	while (stack)
	{
		res = f(node, stack);
		if (res > 0 && (res < close_val || close_val < 0))
		{
			close_val = res;
			close_ind = i;
		}
		i++;
		stack = stack->next;
	}
	if (close_val > 0)
		return (ft_tern_int(close_ind < (i / 2), close_ind
				, -(i - close_ind)));
	return (ft_tern_int(extrem_ind < (i / 2), extrem_ind
			, -(i - extrem_ind)));
}

void	calc_push(int opt, t_list *stack_fr, t_list *stack_to
				, int (*f)(t_list *, t_list *))
{
	t_push	val;
	t_push	temp;
	int		extrem_ind;
	int		size;
	int		i;

	extrem_ind = find_extrem(stack_to, opt);
	size = ft_lstsize(stack_fr);
	val = (t_push){1000, 1000};
	i = 0;
	while (stack_fr)
	{
		temp = (t_push){1000, 1000};
		stack_to = *get_stack(opt);
		temp.score_b = calc_score(stack_fr, stack_to, f, extrem_ind);
		temp.score_a = ft_tern_int(i <= ((size) / 2), i, -(size - i));
		val = push_compare(val, temp);
		i++;
		stack_fr = stack_fr->next;
	}
	do_push(val, opt);
	if (opt)
		return (do_func_print(get_cmds()[3]));
	return (do_func_print(get_cmds()[2]));
}

void	sort_2(void)
{
	t_list	*stack;

	stack = *get_stack(0);
	if (ft_lstsize(stack) < 2 || !stack->next)
		return ;
	if (!ft_lstsorted(*get_stack(0), &is_increasing))
		do_func_print(get_cmds()[0]);
}

void	sort_3(void)
{
	t_list	*stack;
	int		a;
	int		b;
	int		c;

	stack = *get_stack(0);
	if (ft_lstsize(stack) <= 2)
		return (sort_2());
	a = *(int *)stack->content;
	b = *(int *)stack->next->content;
	c = *(int *)stack->next->next->content;
	if (c > b && b > a)
		return ;
	else if (a > b && a > c)
	{
		do_func_print(get_cmds()[4]);
		if (!ft_lstsorted(*get_stack(0), &is_increasing))
			do_func_print(get_cmds()[0]);
	}
	else if (b > a && c > a)
		return (do_func_print(get_cmds()[6]), do_func_print(get_cmds()[0]));
	else if (b > a && b > c)
		do_func_print(get_cmds()[6]);
	else if (a > b && c > b)
		do_func_print(get_cmds()[0]);
}
