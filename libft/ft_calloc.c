/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:16:38 by marvin            #+#    #+#             */
/*   Updated: 2024/08/18 22:16:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
