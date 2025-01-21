/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:53:03 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/20 12:22:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../../libft/libft.h"

typedef struct s_push
{
	int	score_a;
	int	score_b;
}	t_push;

/*		main.c			*/
/************************/
int		is_increasing(t_list *lst);

/*		parser.c		*/
/************************/
int		*parse_imput(size_t ac, char **av);

/*		global.c		*/
/************************/
t_list	**get_stack(int opt);
char	**get_cmds(void);
int		*get_values(int ac, char **av);

/*		commands_1.c	*/
/************************/
void	ft_s(t_list **stack);
void	ft_p(t_list **stack_to, t_list **stack_from);
void	ft_r(t_list **stack);
void	ft_rr(t_list **stack);

/*		commands_2.c	*/
/************************/
void	ft_sab(void);
void	ft_rab(void);
void	ft_rrab(void);

/*		do_funcs.c		*/
/************************/
int		do_func(char *cmd);
void	do_func_print(char *cmd);

/*		do_push.c		*/
/************************/
void	calc_push(int opt, t_list *stack_fr, t_list *stack_to,
			int (*f)(t_list *, t_list *));
int		find_extrem(t_list *stack, int opt);
void	sort_3(void);

/*		struct_func.c	*/
/************************/
t_push	push_compare(t_push p_a, t_push p_b);
void	do_push(t_push val, int opt);

/*		ends.c			*/
/************************/
void	fall_back(int *values, char **temp);
void	free_temp(char **temp);
void	free_all(void);

#endif