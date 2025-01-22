/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:14:44 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/22 14:53:06 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
	int		*f_id;
	int		*p_fd;
	char	**cmd_arg;
	char	*cmd_path;
	int		fd_out;
	int		fd_in;
	int		here_doc;
	int		nb_cmd;
}	t_data;

/********************************/
/*			data.c				*/
/********************************/
void	init_data(t_data *data, int ac, char **av, char **env);
int		clean_data(t_data *data);

/********************************/
/*			data.c				*/
/********************************/
char	*get_path(t_data *data);
int		clean_func(t_data *data);

#endif