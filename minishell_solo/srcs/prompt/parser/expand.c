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

t_list	*add_wildcard(char *line)
{
	int			i;
	char		**path;
	t_list		*dir_path;
	t_list		*tmp;
	t_list		*matches;
	t_list		*match_temp;
	struct stat	path_stat;

	path = ft_split(line, '/');
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
	return (dir_path);
}

t_list	*join_wildcard(t_list *wildcard_expanded)
{
	t_list		*temp;
	t_list		*result;
	int			i;

	temp = wildcard_expanded;
	result = NULL;
	while (temp)
	{
		i = -1;
		while (((char *)temp->content)[++i])
			add_link(&result, ft_strdup(&((char *)temp->content)[i]));
		if (temp->next)
			add_link(&result, ft_strdup(" "));
		wildcard_expanded = temp->next;
		ft_lstdelone(temp, ft_del);
		temp = wildcard_expanded;
	}
	return (result);
}

char	*expand_wildcards(char *line)
{
	int		i;
	int		j;
	char	**splited;
	t_list	*result;

	if (!line)
		return (NULL);
	i = -1;
	result = NULL;
	splited = ft_split_set(line, " \t");
	if (!splited)
		return (NULL);
	while (splited[++i])
	{
		if (ft_strchr(splited[i], '*'))
			ft_lstadd_back(&result, join_wildcard(add_wildcard(splited[i])));
		else
		{
			j = -1;
			while (splited[i][++j])
				add_link(&result, ft_strdup(&splited[i][j]));
		}
	}
	ft_free_tab((void **)splited, i);
	return (ft_lstjoin(result));
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
