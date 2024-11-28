/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:03:59 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 10:44:03 by hle-hena         ###   ########.fr       */
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

/* void	do_block_func(char *cmd, t_list **s_a, t_list **s_b)
{
	if (!cmd)
		return ;
	
} */

void	do_rev_func(char *cmd, t_list **s_a, t_list **s_b)
{
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd, "sa", 4))
		ft_s(s_a, 0);
	else if (!ft_strncmp(cmd, "sb", 4))
		ft_s(s_b, 1);
	else if (!ft_strncmp(cmd, "pa", 4))
		ft_p(s_b, s_a, 0);
	else if (!ft_strncmp(cmd, "pb", 4))
		ft_p(s_a, s_b, 1);
	else if (!ft_strncmp(cmd, "ra", 4))
		ft_rr(s_a, s_b, 0);
	else if (!ft_strncmp(cmd, "rb", 4))
		ft_rr(s_b, s_a, 0);
	else if (!ft_strncmp(cmd, "rra", 4))
		ft_r(s_a, s_b, 0);
	else if (!ft_strncmp(cmd, "rrb", 4))
		ft_r(s_b, s_a, 0);
	else if (!ft_strncmp(cmd, "ss", 4))
		ft_sab(s_a, s_b);
	else if (!ft_strncmp(cmd, "rr", 4))
		ft_rrab(s_a, s_b);
	else if (!ft_strncmp(cmd, "rrr", 4))
		ft_rab(s_a, s_b);
}

int	do_func(char *cmd, t_list **s_a, t_list **s_b)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "sa", 4))
		return (ft_s(s_a, 0));
	else if (!ft_strncmp(cmd, "sb", 4))
		return (ft_s(s_b, 1));
	else if (!ft_strncmp(cmd, "pa", 4))
		return (ft_p(s_a, s_b, 0));
	else if (!ft_strncmp(cmd, "pb", 4))
		return (ft_p(s_b, s_a, 1));
	else if (!ft_strncmp(cmd, "ra", 4))
		return (ft_r(s_a, s_b, 0));
	else if (!ft_strncmp(cmd, "rb", 4))
		return (ft_r(s_b, s_a, 0));
	else if (!ft_strncmp(cmd, "rra", 4))
		return (ft_rr(s_a, s_b, 0));
	else if (!ft_strncmp(cmd, "rrb", 4))
		return (ft_rr(s_b, s_a, 0));
	else if (!ft_strncmp(cmd, "ss", 4))
		return (ft_sab(s_a, s_b));
	else if (!ft_strncmp(cmd, "rr", 4))
		return (ft_rab(s_a, s_b));
	else if (!ft_strncmp(cmd, "rrr", 4))
		return (ft_rrab(s_a, s_b));
	return (-1);
}
