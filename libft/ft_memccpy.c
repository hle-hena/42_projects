/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:13:55 by marvin            #+#    #+#             */
/*   Updated: 2024/08/17 12:13:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && ((unsigned char *) src)[i])
	{
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
		if (((unsigned char *) src)[i] == (unsigned char) c)
			return (&(((unsigned char *) dest)[i + 1]));
		i ++;
	}
	return (0);
}
