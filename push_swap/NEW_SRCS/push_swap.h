/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:51:58 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/22 15:27:23 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
#include <stdio.h>

# define FUTUR_SIGHT 3

/*		main.c			*/
/************************/
void	print(void *content);
int		is_decreasing(t_list *lst);
int		is_increasing(t_list *lst);

/*		parser.c		*/
/************************/
int		*parse_imput(size_t ac, char **av);

/*		get_global.c	*/
/************************/
t_list	**get_stack(int opt);
t_list	**get_cpy(int opt);
char	**get_cmds(void);
int		*get_values(int ac, char **av);

/*		ps_cmd.c		*/
/************************/
int		ft_s(t_list **stack, int witch);
int		ft_p(t_list **stack_to, t_list **stack_from, int witch);
int		ft_r(t_list **stack, t_list **chk, int witch);
int		ft_rr(t_list **stack, t_list **chk, int witch);

/*		ps_cmd.c		*/
/************************/
int		ft_s_res(t_list **stack, int witch);
int		ft_p_res(t_list *lst_top, t_list *lst_bot, t_list *lst_p, int witch);
int		ft_r_res(t_list **stack, t_list **chk, int witch);
int		ft_rr_res(t_list **stack, t_list **chk, int witch);

/*		ps_cmd_ab.c		*/
/************************/
void	ft_sab(t_list **stack_b, t_list **stack_a, int witch);
void	ft_rrab(t_list **stack_b, t_list **stack_a, int witch);
void	ft_rrab(t_list **stack_b, t_list **stack_a, int witch);

/*		tests.c			*/
/************************/
int		do_tests(int pos, size_t last);

/*		do_func.c		*/
/************************/
int		do_op(t_list *node1, t_list *node2);
int		do_func(char *cmd, t_list **s_a, t_list **s_b);
void	do_rev_func(char *cmd, t_list **s_a, t_list **s_b);

/*		ends.c			*/
/************************/
void	fall_back(int *values);
void	free_all(void);

#endif