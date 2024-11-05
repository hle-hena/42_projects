/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:16:38 by marvin            #+#    #+#             */
/*   Updated: 2024/11/05 08:29:34 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*pt;

	if (size != 0 && n > (-1 / size))
		return (0);
	pt = malloc(n * size);
	if (!pt)
		return (NULL);
	ft_bzero(pt, n * size);
	return (pt);
}
