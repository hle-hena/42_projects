/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:16:38 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 17:14:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*dest;
	size_t	i;

	if (size != 0)
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
