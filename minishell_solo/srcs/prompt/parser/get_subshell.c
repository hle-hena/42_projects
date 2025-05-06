/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_subshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:46:02 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/06 11:41:48 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*get_subshell(char *line, int *forward, char **sep)
{
	t_cmd	*cmd;
	char	*str;
	int		err;
	int		separator;
	int		i;

	i = 0;
	separator = 0;
	str = get_parenthesis(line, &i, &err);
	if (err)
		return (*forward += i, *sep = str, NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->args = NULL;
	cmd->ast = get_ast(str, sep);
	if (!cmd->ast)
		return (NULL);
	while (line[i])
	{
		str = tokenize(&line[i], &i, &err, &separator);
		*sep = str;
		if (err)
			return (*forward += i, clear_cmd(cmd, NULL, NULL), NULL);
		else if (separator)
			return (*forward += i, cmd);
		else if (str[0] == '>' || str[0] == '<')
		{
			if (get_redirect(&line[i], &i, cmd, &str))
				return (*forward += i, *sep = str, clear_cmd(cmd, NULL, NULL), NULL);
		}
		else
			return (*forward += i, *sep = str, clear_cmd(cmd, NULL, NULL), NULL);
	}
	return (*forward += i, *sep = NULL, cmd);
}
