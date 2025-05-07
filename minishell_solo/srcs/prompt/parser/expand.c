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

void	print_lst(t_list *lst)
{
	while (lst)
	{
		if (lst->content)
			printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

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

t_list	*wildcards(char *line, char	*path_to_open)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*result;

	result = NULL;
	if (!path_to_open[0])
		dir = opendir(".");
	else
		dir = opendir(path_to_open);
	if (!dir)
	{
		add_link(&result, ft_strdup(line));
		return (result);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue;
		}
		if (match_pattern(entry->d_name, line))
			add_link(&result, ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	return (result);
}

t_list	*add_wildcard(char *line, int *forward)
{
	int			i;
	char		*to_replace;
	char		**path;
	t_list		*dir_path;
	t_list		*tmp;
	t_list		*matches;
	t_list		*match_temp;
	struct stat	path_stat;

	i = 0;
	while (!ft_isspace(line[i]) && line[i])
		i++;
	to_replace = ft_substr(line, 0, i);
	if (!to_replace)
		return (NULL);
	path = ft_split(to_replace, '/');
	free(to_replace);
	if (!path)
		return (NULL);
	dir_path = NULL;
	add_link(&dir_path, ft_strdup(""));
	i = -1;
	while (path[++i])
	{
		tmp = NULL;
		while (dir_path)
		{
			if (!*(char *)dir_path->content)
				stat(".", &path_stat);
			else
				stat(dir_path->content, &path_stat);
			if (!S_ISDIR(path_stat.st_mode))
			{
				dir_path = dir_path->next;
				continue ;
			}
			if (ft_strchr(path[i], '*'))
			{
				matches = wildcards(path[i], dir_path->content);
				match_temp = matches;
				while (matches)
				{
					if (!*(char *)dir_path->content)
						add_link(&tmp, ft_strdup(matches->content));
					else
						add_link(&tmp, ft_strsjoin((char *[]){dir_path->content,
								"/", matches->content, NULL}));
					matches = matches->next;
				}
				ft_lstclear(&match_temp, ft_del);
			}
			else
			{
				if (!*(char *)dir_path->content)
					add_link(&tmp, ft_strdup(path[i]));
				else
					add_link(&tmp, ft_strsjoin((char *[]){dir_path->content,
							"/", path[i], NULL}));
			}
			dir_path = dir_path->next;
		}
		ft_lstclear(&dir_path, ft_del);
		dir_path = tmp;
	}
	ft_free_tab((void **)path, i);
	*forward += i;
	print_lst(dir_path);
	return (dir_path);
}

char	*join_wildcard(t_list *wildcard_expanded)
{
	t_list		*temp;
	char		*result;
	char		*result_temp;

	temp = wildcard_expanded;
	result = ft_strdup("");
	while (temp)
	{
		if (result[0])
			result_temp = ft_strsjoin((char *[]){result, " ", temp->content, NULL});
		else
			result_temp = ft_strdup(temp->content);
		wildcard_expanded = temp->next;
		ft_del((void **)temp);
		temp = wildcard_expanded;
		ft_del((void **)&result);
		result = result_temp;
	}
	return (result);
}

char	*expand_wildcards(char *line)
{
	int		i;
	int		last_space;
	t_list	*result;

	if (!line)
		return (NULL);
	i = -1;
	last_space = -1;
	result = NULL;
	while (line[++i])
	{
		if (ft_isspace(line[i]))
			last_space = i;
		if (line[i] == '*')
		{
			ft_lstadd_back(&result, add_wildcard(&line[last_space + 1], &last_space));
			i = last_space;
		}
		else
			add_link(&result, ft_strdup(&line[i]));
	}
	return (join_wildcard(result));
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
	return (ft_del((void **)&str), expand_wildcards(ft_lstjoin(line)));
}
