/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:40:04 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/07 15:27:56 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
	if (line[0] == '/')
		add_link(&dir_path, ft_strdup("/"));
	else
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
					else if (i == 0 && *(char *)dir_path->content == '/')
						add_link(&tmp, ft_strsjoin((char *[]){dir_path->content,
								matches->content, NULL}));
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

t_list	*join_wildcard(t_list *wildcard_expanded, char *standard)
{
	t_list		*temp;
	t_list		*result;
	int			i;

	if (!wildcard_expanded)
	{
		i = -1;
		while (standard[++i])
			add_link(&result, ft_strdup(&standard[i]));
		return (result);
	}
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

t_list	*split_wildcard(char *line)
{
	int		s;
	int		e;
	t_list	*split;

	s = 0;
	e = -1;
	split = NULL;
	while (line[++e])
	{
		if (ft_strchr(" \t|&()><", line[e]))
		{
			add_link(&split, ft_substr(line, s, e - s));
			s = e;
			while (ft_strchr(" \t|&()><", line[e]))
				e++;
			add_link(&split, ft_substr(line, s, e - s));
			s = e;
		}
	}
	add_link(&split, ft_substr(line, s, e - s));
	return (split);
}

char	*expand_wildcards(char *line)
{
	int		i;
	int		j;
	t_list	*splited;
	t_list	*temp;
	t_list	*result;

	if (!line)
		return (NULL);
	printf("Line is {%s}\n", line);
	i = -1;
	result = NULL;
	splited = split_wildcard(line);
	if (!splited)
		return (NULL);
	temp = splited;
	while (temp)
	{
		if (ft_strchr(temp->content, '*'))
			ft_lstadd_back(&result, join_wildcard(add_wildcard(temp->content), temp->content));
		else
		{
			j = -1;
			while (((char *)temp->content)[++j])
				add_link(&result, ft_strdup(&((char *)temp->content)[j]));
		}
		if (temp->next)
			add_link(&result, ft_strdup(" "));
		temp = temp->next;
	}
	ft_lstclear(&splited, ft_del);
	return (ft_lstjoin(result));
}
