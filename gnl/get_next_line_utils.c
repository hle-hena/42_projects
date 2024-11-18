/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:46:35 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/18 11:15:18 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_tern_str(int cnd, char *ret1, char *ret2)
{
	if (cnd)
		return (ret1);
	return (ret2);
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

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *) str);
		str ++;
	}
	if ('\0' == (char)c)
		return ((char *) str);
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*ret;

	s1_len = -1;
	while (s1[++ s1_len])
		;
	s2_len = -1;
	while (s2[++ s2_len])
		;
	ret = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!ret)
		return (0);
	i = -1;
	while (++ i < s1_len)
		ret[i] = s1[i];
	while (i < s1_len + s2_len)
	{
		ret[i] = s2[i - s1_len];
		i ++;
	}
	return (ret);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	len;

	len = 0;
	if (!src)
		return (NULL);
	while (src[len])
		len ++;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (0);
	i = -1;
	while (++ i < len)
		dest[i] = src[i];
	dest[i] = 0;
	return (dest);
}
