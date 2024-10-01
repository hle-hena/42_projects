/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:31:14 by marvin            #+#    #+#             */
/*   Updated: 2024/08/16 18:31:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *add, int oct, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)add)[i] = (unsigned char)oct;
		i ++;
	}
	return (add);
}
