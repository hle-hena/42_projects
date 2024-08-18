/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:55:20 by marvin            #+#    #+#             */
/*   Updated: 2024/08/17 19:55:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *add1, const void *add2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) add1)[i] != ((unsigned char *) add2)[i])
			return (((unsigned char *) add1)[i] - ((unsigned char *) add2)[i]);
		i ++;
	}
	return (0);
}
