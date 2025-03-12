/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:00:05 by hle-hena          #+#    #+#             */
/*   Updated: 2025/02/05 13:00:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <signal.h>
#include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

#define S_ERR "mini: syntax error near unexpected token `"

char	*get_color(int option);
int		set_colors(char	*col1, char *col2, char *col3, char *col4);
void	print_welcome(void);

/* -------------------------------------------------------------------------- */
/*                  wildcard.c                                                  */
/* -------------------------------------------------------------------------- */
char **wildcard(char **str, int j);

/* -------------------------------------------------------------------------- */
/*                  get_var.c                                                  */
/* -------------------------------------------------------------------------- */
char	*get_var(char *str);

/* -------------------------------------------------------------------------- */
/*                  fill.c                                                  */
/* -------------------------------------------------------------------------- */
void	fill_exe(t_pars **pars, int i, int j);
int	fill_struct(t_pars *cmd, char **arg, int *n_arg);

/* -------------------------------------------------------------------------- */
/*                  parser.c                                                  */
/* -------------------------------------------------------------------------- */
int	parseur(char *line, t_data **d);

/* -------------------------------------------------------------------------- */
/*                  prompt.c                                                  */
/* -------------------------------------------------------------------------- */
void	new_prompt(int signum);
char	*get_prompt();
void	any(int signum);

/* -------------------------------------------------------------------------- */
/*                  utils.c                                                   */
/* -------------------------------------------------------------------------- */
int	ft_strchri(char *str, char *c);
int	nbr_sep(char **str, char *sep);
char	*ft_strdelchar(char *str, char del);
void	free_tpars(t_pars **pars);
void	shift_left(char **str, size_t i);

/* -------------------------------------------------------------------------- */
/*                  utils_lst.c                                               */
/* -------------------------------------------------------------------------- */
t_pars *init_struct_pars(char **split, int nbr);
void	init_struct_cmd(t_pars **pars, int nbr, char **arg);
char	**ft_split2(char *s, char *c);







t_bt	*create_bt_node(void *content);
t_bt	*ft_btnew(void *content);
void	set_parent(t_bt *parent, t_bt *child, int right);
t_list	*get_cmd(char *line);
char	*ft_lstjoin(t_list *lst);
t_list	*get_quote(char *line, int quote_type, int *forward);
t_list	*get_var_new(char *line, int *forward);
t_list	*get_parenthesis(char *line, int *forward, int *err);
t_cmd	*get_next_cmd(char *line, int *forward, char **sep);
char	*get_next_block(char *line, int *forward, int *err);







#endif