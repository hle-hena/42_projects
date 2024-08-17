/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:45:01 by marvin            #+#    #+#             */
/*   Updated: 2024/08/17 12:45:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memmove(void *dest, void *src, size_t n)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = ((unsigned char *) src);
	while (temp[i] && i < n)
	{
		((unsigned char *) dest)[i] = temp[i];
		i ++;
	}
	return (dest);
}
