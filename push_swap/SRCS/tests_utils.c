/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:03:59 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/14 19:39:39 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	do_op(t_list *node1, t_list *node2)
{
	if (node1 && node2)
		return (*(int *)node1->content - *(int *)node2->content);
	else if (node1)
		return (*(int *)node1->content);
	else
		return (-*(int *)node2->content);
}

t_list	*get_closest(t_list *node, t_list *stack)
{
	t_list	*last;
	int		res_f;
	int		res_l;

	last = ft_lstlast(stack);
	res_f = do_op(node, stack);
	if (res_f < 0)
		res_f = -res_f;
	res_l = do_op(node, last);
	if (res_l < 0)
		res_l = -res_l;
	if (res_l < res_f)
		return (last);
	return (stack);
}

int	do_func_rr(char *cmd, t_list **s_a, t_list **s_b)
{
	t_list	*closest_prev;
	t_list	*closest_actu;

	if (!ft_strncmp(cmd, "rra", 4))
	{
		ft_ra(s_a);
		closest_prev = get_closest((*s_a)->next, *s_b);
		closest_actu = get_closest(*s_a, *s_b);
		return (do_op((*s_a)->next, closest_prev) - do_op(*s_a, closest_actu));
	}
	else if (!ft_strncmp(cmd, "rrb", 4))
	{
		ft_rb(s_b);
		closest_prev = get_closest((*s_b)->next, *s_a);
		closest_actu = get_closest(*s_b, *s_a);
		return (do_op((*s_b)->next, closest_prev) - do_op(*s_b, closest_actu));
	}
	return (-1);
}

int	do_func_r(char *cmd, t_list **s_a, t_list **s_b)
{
	t_list	*closest_prev;
	t_list	*closest_actu;
	t_list	*l_a;
	t_list	*l_b;

	l_a = ft_lstlast(*s_a);
	l_b = ft_lstlast(*s_b);
	if (!ft_strncmp(cmd, "ra", 4))
	{
		ft_ra(s_a);
		closest_prev = get_closest(l_a, *s_b);
		closest_actu = get_closest(*s_a, *s_b);
		return (do_op(l_a, closest_prev) - do_op(*s_a, closest_actu));
	}
	else if (!ft_strncmp(cmd, "rb", 4))
	{
		ft_rb(s_b);
		closest_prev = get_closest(l_b, *s_a);
		closest_actu = get_closest(*s_b, *s_a);
		return (do_op(l_b, closest_prev) - do_op(*s_b, closest_actu));
	}
	return (-1);
}

int	do_func(char *cmd, t_list **s_a, t_list **s_b)
{
	if (!ft_strncmp(cmd, "sa", 4))
		return (ft_sa(s_a), do_op((*s_a)->next, *s_a));
	else if (!ft_strncmp(cmd, "sb", 4))
		return (ft_sb(s_b), do_op(*s_b, (*s_b)->next));
	else if (!ft_strncmp(cmd, "pa", 4))
		return (ft_pa(s_a, s_b), do_op((*s_a)->next, *s_a));
	else if (!ft_strncmp(cmd, "pb", 4))
		return (ft_pb(s_b, s_a), do_op(*s_b, (*s_b)->next));
	else if (cmd[1] == 'r')
		return (do_func_rr(cmd, s_a, s_b));
	else if (cmd[0] == 'r')
		return (do_func_r(cmd, s_a, s_b));
	return (-1);
}
