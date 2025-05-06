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

#include <dirent.h>

int	match_pattern(const char *str, const char *pattern)
{
	if (!*pattern)
		return (!*str);
	if (*pattern == '*')
	{
		while (*str)
		{
			if (match_pattern(str, pattern + 1))
				return (1);
			str++;
		}
		return (match_pattern(str, pattern + 1));
	}
	else if (*pattern == *str)
		return (match_pattern(str + 1, pattern + 1));
	else
		return (0);
}


char	*wildcards(char *line)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*result;
	int				first;

	first = 1;
	if (!ft_strchr(line, '*'))
		return (line);
	dir = opendir(".");
	if (!dir)
		return (line);
	result = ft_strdup("");
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue;
		if (ft_strncmp(line, "*", 2) == 0 || match_pattern(entry->d_name, line))
		{
			if (!first)
				result = ft_strjoin_free(result, " ");
			result = ft_strjoin_free(result, entry->d_name);
			first = 0;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	if (!result)
		return (line);
	return (result);
}

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
			i++;
		else if (str[i] == '$' && (!in_quote || in_quote == 34))
			ft_lstadd_back(&line, get_var(&str[i], &i));
		else if (str[i] == '*' && str[i + 1] == '*')
			i++;
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
	return (ft_del((void **)&str), wildcards(ft_lstjoin(line)));
}
