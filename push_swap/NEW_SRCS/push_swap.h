/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:58 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 10:58:48 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

# define FUTUR_SIGHT 5
# define INT_MIN -2147483647

/*		main.c			*/
/************************/
void	print(void *content);
int		is_decreasing(t_list *lst);
int		is_increasing(t_list *lst);

/*		parser.c		*/
/************************/
int		*parse_imput(size_t ac, char **av);

/*		global.c		*/
/************************/
t_list	**get_stack(int opt);
char	**get_cmds(void);
int		*get_values(int ac, char **av);
t_list	**get_states(int opt);

/*		ps_cmd.c		*/
/************************/
int		ft_s(t_list **stack, int witch);
int		ft_p(t_list **stack_to, t_list **stack_from, int witch);
int		ft_r(t_list **stack, t_list **chk, int res);
int		ft_rr(t_list **stack, t_list **chk, int witch);

/*		ps_cmd.c		*/
/************************/
int		ft_s_res(t_list **stack, int witch);
int		ft_p_res(t_list *lst_top, t_list *lst_bot, t_list *lst_p, int witch);
int		ft_r_res(t_list *stack, t_list *other_stack);
int		ft_rr_res(t_list *stack, t_list *oth_stack);

/*		ps_cmd_ab.c		*/
/************************/
int		ft_sab(t_list **stack_b, t_list **stack_a);
int		ft_rab(t_list **stack_b, t_list **stack_a);
int		ft_rrab(t_list **stack_b, t_list **stack_a);

/*		tests.c			*/
/************************/
int		do_tests(int pos, size_t last);

/*		states.c		*/
/************************/
int		check_state(int i);
void	add_states();

/*		do_func.c		*/
/************************/
int		do_op(t_list *node1, t_list *node2);
int		do_func(char *cmd, t_list **s_a, t_list **s_b);
void	do_rev_func(char *cmd, t_list **s_a, t_list **s_b);

/*		ends.c			*/
/************************/
void	fall_back(int *values, char **temp);
void	free_all(void);
void	free_temp(char **temp);

#endif