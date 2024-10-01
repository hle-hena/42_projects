/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:21:14 by marvin            #+#    #+#             */
/*   Updated: 2024/08/17 20:21:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	size;
	
	i = 0;
	size = 0;
	while (src[size])
		size ++;
	if (n == 0)
		return (size);
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i ++;
	}
	dest[i] = 0;
	return (size);
}
