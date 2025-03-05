/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:28:35 by hle-hena          #+#    #+#             */
/*   Updated: 2025/03/05 13:16:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// int	block_is_empty(char *str)
// {
// 	int	ret;

// 	if (!str)
// 		return (1);
// 	while (*str)
// 	{
// 		if (!ft_isspace(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// int		get_blocks_size(t_list *blocks)
// {
// 	t_list	*temp;
// 	int		size;

// 	size = 0;
// 	temp = blocks;
// 	while (temp)
// 	{
// 		if (block_is_empty(temp->content))
// 			return (ft_perror(-1, "mini: syntax error near unexpected token `||'", 0), -1);
// 		size += ft_strlen(temp->content);
// 		temp = temp->next;
// 		if (temp)
// 			temp = temp->next;
// 	}
// 	return (size + 1);
// }

// char	**join_blocks(t_list *blocks)
// {
// 	int		size;
// 	char	**ret_str;

// 	size  = get_blocks_size(blocks);
// 	if (size == -1)
// 		return (NULL);
// 	ret_str = malloc((ft_lstsize(blocks) + 1) * sizeof(char *));
// 	if (!ret_str)
// }

// char	**get_blocks(char *line)
// {
// 	t_list	*blocks;
// 	t_list	*sep;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	while (line[++i])
// 	{
// 		if ((line[i] == '|' && line[i + 1] == '|')
// 			|| (line[i] == '&' && line[i + 1] == '&'))
// 		{
// 			add_link(&blocks, ft_substr(line, j, j - i));
// 			add_link(&blocks, ft_substr(line, i, 2));
// 			j = i + 2;
// 			i ++;
// 		}
// 	}
// }

int	get_eop(char *str)
{
	int	i;
	int	depth;

	i = 0;
	depth = 1;
	while (str[++i])
	{
		if (str[i] == ')')
			depth--;
		if (str[i] == '(')
			depth++;
		if (depth == 0)
			return (i);
	}
}

t_list	*get_blocks(char *line)
{
	t_list	*blocks;
	int		i;
	int		j;
	int		add;

	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '(')
		{
			i += get_eop(line[i]);
			add = 1;
		}
		if ((line[i] == '|' && line[i + 1] == '|')
			|| (line[i] == '&' && line[i + 1] == '&'))
			add = 1;
		if (add)
		{
			add_link(&blocks, ft_strtrim(ft_substr(line, j, j - i), " ()"));
			add_link(&blocks, ft_strtrim(ft_substr(line, i++, 2), " "));
			j = ++i;
			add = 0;
		}
	}
}
