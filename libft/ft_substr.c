/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:53:33 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/05 11:33:27 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*dest;

	if (start >= ft_strlen(src))
		return (ft_strdup(""));
	if (len > ft_strlen(src) - start)
		len = ft_strlen(src) - start;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (0);
	ft_strlcpy(dest, &src[start], len + 1);
	return (dest);
}
