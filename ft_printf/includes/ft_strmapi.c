/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 19:07:13 by marvin            #+#    #+#             */
/*   Updated: 2024/08/20 19:07:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	dest = ft_strdup(str);
	i = 0;
	if (!dest)
		return (0);
	while (dest[i])
	{
		dest[i] = f(i, dest[i]);
		i ++;
	}
	return (dest);
}
