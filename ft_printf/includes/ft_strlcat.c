/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:50:34 by marvin            #+#    #+#             */
/*   Updated: 2024/08/18 11:50:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (n <= dest_len)
		return (src_len + n);
	while (src[i] && i < n - dest_len - 1)
	{
		dest[i + dest_len] = src[i];
		i ++;
	}
	dest[i + dest_len] = '\0';
	return (dest_len + src_len);
}
