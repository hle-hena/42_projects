/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:05:10 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/06 11:35:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/* -------------------------------------------------------------------------- */
/*                  exec.h                                                    */
/* -------------------------------------------------------------------------- */
// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list	*next;
// }	t_list;

/* -------------------------------------------------------------------------- */
/*                  exec.h                                                    */
/* -------------------------------------------------------------------------- */
typedef struct s_info_cmd
{
	int		fd_in;
	int		fd_out;
	char	*here_doc;
	char	*path;
	char	**args;
	int		define;
	int		pipe[2];
	int		pid;
	int		exit;
}	t_icmd;

typedef struct s_bt
{
	void		*content;
	int			value;
	struct s_bt	*parent;
	struct s_bt	*left;
	struct s_bt	*right;
}	t_bt;

/* 
	Modes :
		0 - out, truncate
		1 - out, append
		2 - in, normal
		3 - in, heredoc
		4 - in out, both in that order
*/
typedef struct s_open
{
	int		mode;
	char	*str;
}	t_op;

typedef struct s_cmd
{
	t_list	*open;
	t_bt	*ast;
	char	**args;
}	t_cmd;

/* -------------------------------------------------------------------------- */
/*                  prompt.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_pars
{
	int		n_sep;
	int		pipe;
	char	*in;
	char	*out;
	char	*cmd;
	char	*limiter;
	char	*append;
	char	sep;
	char	**split;
	char	*line;
	char	*before;
	t_cmd *exe;
}		t_pars;

/* -------------------------------------------------------------------------- */
/*                  data.h                                                  */
/* -------------------------------------------------------------------------- */
typedef struct s_data
{
	t_pars	*cmd;
	t_icmd	*cmds;
	t_list	*imp;
	t_list	*env;
	t_list	*loc;
	int		nb_cmds;
	int		saved_out;
	int		saved_tty;
}	t_data;

#endif