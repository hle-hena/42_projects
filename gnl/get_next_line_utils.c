/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:15:12 by marvin            #+#    #+#             */
/*   Updated: 2024/09/03 20:21:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*ret;

	s1_len = -1;
	s2_len = -1;
	i = 0;
	while (s1[++s1_len]);
	while (s2[++s2_len]);
	ret = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!ret)
		return (0);
	ret[0] = 0;
	while (*s1)
		ret[i++] = *s1++;
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = 0;
	return (ret);
}

int	ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char) c)
			return (1);
		str ++;
	}
	return (0);
}

char	*ft_trimend(const char *str)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = 0;
	if (str[0] == '\n')
		return (ft_calloc(1, sizeof(char)));
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[len] = '\0';
	return (res);
}

char	*ft_trimstart(const char *str)
{
	size_t  start;
	size_t  i;
	size_t	strlen;
	char	*result;

	start = 0;
	while (str[start] != '\0' && str[start] != '\n')
		start++;
	if (str[start] == '\0')
		return (ft_calloc(1, sizeof(char)));
	start++;
	strlen = 0;
	while (str[strlen++]);
	result = ft_calloc((strlen - start + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (str[start + i] != '\0')
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
