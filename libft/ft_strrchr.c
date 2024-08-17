/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:07:01 by marvin            #+#    #+#             */
/*   Updated: 2024/08/16 19:07:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(char *str, int c)
{
	char	*last;

	last = 0;
	while (*str)
	{
		if (*str == (char)c)
			last = str;
		str ++;
	}
	if (*str == (char)c)
		last = str;
	return (last);
}
