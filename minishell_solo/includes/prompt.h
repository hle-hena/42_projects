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
char	*ft_lstjoin(t_list *lst);
t_list	*get_quote(char *line, int quote_type, int *forward);
t_list	*get_var(char *line, int *forward);
t_list	*get_parenthesis(char *line, int *forward, int *err);
t_cmd	*get_next_cmd(char *line, int *forward, char **sep, int err);
char	*get_next_block(char *line, int *forward, int *err);
t_list	*get_next_pipeline(char *line, int *forward, char **sep);
void	clear_pipeline(t_list *cmd);
t_list	*get_tilde(int *forward);
void	clear_blocks(t_list *cmds);
t_list	*get_cmds(char *line, char **err_token);
void	clear_cmd(t_cmd *cmd, t_list *args, char *current);
t_bt	*get_ast(char *line);
void	clear_tree(t_bt *tree);
int		run_ast(t_bt *ast);
char	*expand(char *str);
char	*remove_quote(char *str);


#endif