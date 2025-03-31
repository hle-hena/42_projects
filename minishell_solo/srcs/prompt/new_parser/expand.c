/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-18 15:27:09 by hle-hena          #+#    #+#             */
/*   Updated: 2025-03-18 15:27:09 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*expand(char *str)
{
	t_list	*line;
	int		i;
	int		in_quote;

	i = 0;
	in_quote = 0;
	line = NULL;
	while (str[i])
	{
		if (str[i] == '$' && !in_quote && ft_strchr("\'\"", str[i + 1]))
			i ++;
		else if (str[i] == '$' && (!in_quote || in_quote == 34))
			ft_lstadd_back(&line, get_var(&str[i], &i));
		else
		{
			if ((str[i] == 34 || str[i] == 39) && !in_quote)
				in_quote = str[i];
			else if (str[i] == in_quote)
				in_quote = 0;
			add_link(&line, ft_strdup(&str[i]));
			i++;
		}
	}
	return (ft_del((void **)&str), ft_lstjoin(line));
}
