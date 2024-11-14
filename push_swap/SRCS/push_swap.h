/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:58 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/14 19:32:57 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
#include <stdio.h>

# define FUTUR_SIGHT 2

/*		ps_cmd_a.c		*/
/************************/
void	ft_sa(t_list **stack_a);
void	ft_pa(t_list **stack_a, t_list **stack_b);
void	ft_ra(t_list **stack_a);
void	ft_rra(t_list **stack_a);

/*		ps_cmd_b.c		*/
/************************/
void	ft_sb(t_list **stack_b);
void	ft_pb(t_list **stack_b, t_list **stack_a);
void	ft_rb(t_list **stack_b);
void	ft_rrb(t_list **stack_b);

/*		ps_cmd_ab.c		*/
/************************/
t_list	**get_stack(int opt);
void	ft_ss(t_list **stack_b, t_list **stack_a);
void	ft_rr(t_list **stack_b, t_list **stack_a);
void	ft_rrr(t_list **stack_b, t_list **stack_a);

/*		tests.c			*/
/************************/
t_list	*get_sample(t_list *o_stack);

/*		tests_utils.c	*/
/************************/
int	do_func(char *cmd, t_list **s_a, t_list **s_b);

#endif