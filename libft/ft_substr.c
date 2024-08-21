/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 22:35:25 by marvin            #+#    #+#             */
/*   Updated: 2024/08/18 22:35:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	dest_i;
	size_t	tot_i;
	char	*dest;

	dest_i = 0;
	tot_i = start;
	if (start > ft_strlen(s))
		return (0);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest || !s)
		return (0);
	while (dest_i < len && s[tot_i])
	{
		dest[dest_i] = s[tot_i];
		dest_i ++;
		tot_i ++;
	}
	dest[dest_i] = 0;
	return (dest);
}
