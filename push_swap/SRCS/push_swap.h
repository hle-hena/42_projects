/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:58 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/20 14:00:22 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
#include <stdio.h>

# define FUTUR_SIGHT 3

typedef void **	t_vd;

/*		main.c			*/
/************************/
int		is_decreasing(t_list *lst);
int		is_increasing(t_list *lst);

int		*parse_imput(size_t ac, char **av);

/*		ps_cmd_a.c		*/
/************************/
int		ft_s(t_list **stack, int witch);
int		ft_p(t_list **stack_to, t_list **stack_from, int witch);
int		ft_r(t_list **stack, t_list **chk, int witch);
int		ft_rr(t_list **stack, t_list **chk, int witch);

/*		ps_cmd_ab.c		*/
/************************/
t_list	**get_stack(int opt);
void	ft_sab(t_list **stack_b, t_list **stack_a, int witch);
void	ft_rrab(t_list **stack_b, t_list **stack_a, int witch);
void	ft_rrab(t_list **stack_b, t_list **stack_a, int witch);

/*		tests.c			*/
/************************/
char	*init_tests(void);

/*		sample_utils.c	*/
/************************/
t_list	*get_nlast_element(t_list *stack, size_t n);
t_list	*get_sample(t_list *o_stack);

/*		tests_utils.c	*/
/************************/
char	***get_cmds(void);
void	free_tests(char ***tests);

/*		do_func.c		*/
/************************/
int		do_op(t_list *node1, t_list *node2);
t_list	*get_closest(t_list *node, t_list *stack);
int		do_func(char *cmd, t_list **s_a, t_list **s_b);

#endif