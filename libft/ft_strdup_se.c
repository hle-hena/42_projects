/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_se.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:22:51 by marvin            #+#    #+#             */
/*   Updated: 2024/11/04 12:36:36 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_se(const char *src, int s, int e)
{
	char	*dest;
	int		i;

	if (e - s < 0)
		return (0);
	dest = ft_calloc(e - s + 2, sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (i < e - s + 1)
	{
		dest[i] = src[s + i];
		i ++;
	}
	dest[i] = 0;
	return (dest);
}
