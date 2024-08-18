/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:25:59 by marvin            #+#    #+#             */
/*   Updated: 2024/08/16 19:25:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len && str[i])
	{
		j = 0;
		while (j < len && str[i + j] == to_find[j] && to_find[j])
			j ++;
		if (to_find[j] == '\0')
			return ((char *) &str[i]);
		i ++;
	}
	return (0);
}
