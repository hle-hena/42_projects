/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:27:47 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/05 09:50:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *add, int oct, size_t n)
{
	while (n > 0)
	{
		n--;
		((unsigned char *)add)[n] = (unsigned char)oct;
	}
	return (add);
}
