/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:26:34 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/05 16:29:55 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*token_sep(char *line, int *forward, int *err, int temp)
{
	char	*res;
	int		i;

	i = 1;
	if ((line[i] == line[i + 1]) || (line[i] == '<' && line[i + 1] == '>'))
	{
		res = ft_substr(line, 0, 2);
		i = 2;
	}
	else
		res = ft_substr(line, 0, 1);
	*forward += i + temp;
	if (ft_strchr("()", line[0]))
		*err = 1;
	if (ft_strncmp(res, "&", 2) == 0)
		*err = 1;
	return (res);
}

char	*tokenize(char *line, int *forward, int *err, int *sep)
{
	t_list	*head;
	int		i;
	int		quote;

	i = 0;
	head = NULL;
	quote = 0;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strchr("><|&()", line[i]))
		return (*sep = 1, token_sep(&line[i], forward, err, i));
	while (line[i])
	{
		if (line[i] == quote && quote)
			quote = 0;
		else if ((line[i] == '\'' || line[i] == '"') && !quote)
			quote = line[i];
		else if (line[i] == '~' && (!line[i + 1] || line[i + 1] == '/'
				|| ft_isspace(line[i + 1])))
			ft_lstadd_back(&head, get_tilde());
		else if ((ft_isspace(line[i]) || ft_strchr("><|&()", line[i])) && !quote)
			break ;
		else
			add_link(&head, ft_strdup(&line[i]));
		i++;
	}
	*err = (quote != 0);
	return (*forward += i, ft_lstjoin(head));
}
