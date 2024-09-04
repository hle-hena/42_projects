/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:15:12 by marvin            #+#    #+#             */
/*   Updated: 2024/09/04 19:40:12 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	freeing(char **pt)
{
	free(*pt);
	*pt = NULL;
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*dest;
	size_t	i;

	dest = malloc(n * size);
	if (!dest)
		return (0);
	i = 0;
	while (i < n * size)
	{
		((char *) dest)[i] = 0;
		i ++;
	}
	return (dest);
}

char	*ft_recat(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	char	*res;

	len_s1 = -1;
	len_s2 = -1;
	while (s1[++len_s1]);
	while (s2[++len_s2]);
	res = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		res[i] = s1[i];
	free(s1);
	while (*s2)
		res[i++] = *s2++;
	res[i] = 0;
	return (res);
}

int	ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char) c)
			return (i);
		i ++;
	}
	return (-1);
}

char	*ft_strdup_se(const char *src, int s, int e)
{
	char	*dest;
	int		i;

	if (e - s < 0)
		return (0);
	dest = ft_calloc(e - s + 2, sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (i < e - s + 1)
	{
		dest[i] = src[s + i];
		i ++;
	}
	dest[i] = 0;
	return (dest);
}
