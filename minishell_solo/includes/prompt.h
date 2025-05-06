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

char	*get_color(int option);
int		set_colors(char	*col1, char *col2, char *col3, char *col4);
void	print_welcome(void);

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

t_bt	*create_bt_node(void *content);
t_bt	*ft_btnew(void *content);
void	set_parent(t_bt *parent, t_bt *child, int right);
char	*ft_lstjoin(t_list *lst);
t_list	*get_quote(char *line, int quote_type, int *forward);
t_list	*get_var(char *line, int *forward);
char	*get_parenthesis(char *line, int *forward, int *err);
t_cmd	*get_next_cmd(char *line, int *forward, char **sep, int err);
char	*get_next_block(char *line, int *forward, int *err);
t_list	*get_next_pipeline(char *line, int *forward, char **sep);
void	clear_pipeline(t_list *cmd);
t_list	*get_tilde();
void	clear_blocks(t_list *cmds);
t_list	*get_cmds(char *line, char **err_token);
void	clear_cmd(t_cmd *cmd, t_list *args, char *current);
t_bt	*get_ast(char *line, char **err);
void	clear_tree(t_bt *tree);
int		run_ast(t_bt *ast);
char	*expand(char *str);
char	*remove_quote(char *str);
t_bt	*build_tree(t_list *blocks);
char	*tokenize(char *line, int *forward, int *err, int *sep);
t_cmd	*get_subshell(char *line, int *forward, char **sep);
char	*get_redirect(char *line, int *forward, t_cmd *cmd, char **temp);
void	print_ast_recursive(t_bt *node, int depth);


int		clean_icmds(void);
int		ft_color(char **av);

#endif