/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:46:02 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/05 16:31:57 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*get_subshell(char *line, int *forward, char **sep)
{
	t_cmd	*cmd;
	char	*block;
	int		err;
	int		separator;
	int		i;

	i = 0;
	block = tokenize(line, &i, &err, &separator);
	if (err)
		return (*forward += i, *sep = NULL, NULL);
	cmd = malloc(1 * sizeof(t_cmd));
	if (!cmd)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."), clean_data());
	*cmd = (t_cmd){NULL, NULL, 0};
	cmd->args = malloc(2 * sizeof(char *));
	if (!cmd->args)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."), clean_data());
	cmd->args[0] = block;
	cmd->args[1] = NULL;
	if (!line[i])
		return (*forward += i, *sep = NULL, cmd);
	block = tokenize(&line[i], &i, &err, &separator);
	*forward += i;
	if (err)
		return (clear_cmd(cmd, NULL, NULL), *sep = NULL, NULL);
	return (*sep = block, cmd);
}
