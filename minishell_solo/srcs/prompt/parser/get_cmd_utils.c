/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:56:16 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/06 11:08:18 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_lstcpy_one(t_list *lst, int size)
{
	t_list	*next;
	char	*dest;
	int		i;
	
	if (size == 0)
		return (NULL);
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while(++i < size)
	{
		while (((char *)lst->content)[0] == 0 && lst->next)
		{
			next = lst->next;
			ft_lstdelone(lst, ft_del);
			lst = next;
		}
		dest[i] = ((char *)lst->content)[0];
		next = lst->next;
		ft_lstdelone(lst, ft_del);
		lst = next;
	}
	dest[size] = 0;
	return (dest);
}

char	*ft_lstjoin(t_list *lst)
{
	int		size;
	t_list	*temp;

	temp = lst;
	size = 0;
	while (temp)
	{
		while (((char *)(temp->content))[0] == 0 && temp->next)
			temp = temp->next;
		size++;
		temp = temp->next;
	}
	return (ft_lstcpy_one(lst, size));
}

t_list	*get_var(char *line, int *forward)
{
	t_list	*head;
	t_list	*var;
	char	*var_name;
	char	*value;
	int		i;

	i = 1;
	head = NULL;
	var = NULL;
	if (ft_isdigit(line[i]))
		return (*forward += 2, head);
	if (line[i] == '?')
	{
		value = ft_getimp("?");
		while (*value)
			add_link(&head, ft_strdup(&(*value++)));
		return (*forward += 2, head);
	}
	while (ft_isalnum(line[i]) || line[i] == '_')
		add_link(&var, ft_strdup(&line[i++]));
	var_name = ft_lstjoin(var);
	if (!var_name)
		return (*forward += i, ft_lstnew(&line[0]));
	value = ft_getenv(var_name);
	if (!value)
		value = ft_getloc(var_name);
	ft_del((void **)&var_name);
	if (!value)
		return (*forward += i, NULL);
	while (*value)
	{
		if (*value == 34 || *value == 39)
			add_link(&head, ft_strdup("\\")); 
		add_link(&head, ft_strdup(&(*value++)));
	}
	return (*forward += i, head);
}

char	*remove_quote(char *str)
{
	if (str[0] == '\'' || str[0] == '"')
		return (ft_substr(str, 1, ft_strlen(str) - 2));
	return (ft_strdup(str));
}

t_list	*get_quote(char *line, int quote_type, int *forward)
{
	t_list	*head;
	int		i;

	i = 0;
	head = NULL;
	add_link(&head, ft_strdup(&line[i++]));
	while (line[i] != quote_type && line[i])
	{
		if (line[i] == 92 && !line[i + 1])
			return (ft_lstclear(&head, ft_del), NULL);
		if (line[i] == 92)
		{
			add_link(&head, ft_strdup(&line[++i]));
			i++;
			continue ;
		}
		if (quote_type == 39)
			add_link(&head, ft_strdup(&line[i++]));
		else if (line[i] == '$')
			ft_lstadd_back(&head, get_var(&line[i], &i));
		else
			add_link(&head, ft_strdup(&line[i++]));
	}
	add_link(&head, ft_strdup(&line[i]));
	add_link(&head, ft_strdup(""));
	*forward += i;
	if (line[i] != quote_type)
		return (ft_lstclear(&head, ft_del), NULL);//This is an error to print.
	return (head);
}

char	*get_parenthesis(char *line, int *forward, int *err)
{
	t_list	*parenthesis;
	int		depth;
	int		i;

	parenthesis = NULL;
	i = 1;
	depth = ft_tern_int(line[0] == '(', 1, -1);
	if (depth < 0)
		return (*err = 1, ft_strdup(")"));
	while (depth > 0 && line[i])
	{
		if (line[i] == '(')
			depth ++;
		if (line[i] == ')')
			depth --;
		if (depth != 0)
			add_link(&parenthesis, ft_strdup(&line[i]));
		i++;
	}
	while (ft_isspace(line[i]))
		i++;
	*forward += i;
	if (depth != 0)
		return (*err = 1, ft_lstclear(&parenthesis, ft_del), NULL);
	return (*err = 0, ft_lstjoin(parenthesis));
}

t_list	*get_tilde(void)
{
	char	*value;
	t_list	*head;

	head = NULL;
	value = ft_getloc("HOME");
	if (!value)
		value = ft_getenv("HOME");
	if (!value)
		value = ft_getimp("HOME");
	while (*value)
		add_link(&head, ft_strdup(&(*value++)));
	return (head);
}
