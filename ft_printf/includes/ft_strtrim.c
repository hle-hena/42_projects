/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:30:25 by marvin            #+#    #+#             */
/*   Updated: 2024/08/19 12:30:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_instr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i ++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int	s;
	int	e;
	char	*ret;

	e = ft_strlen(s1) - 1;
	s = 0;
	ret = 0;
	while (s <= e && is_instr(set, s1[s]))
		s ++;
	while (e >= 0 && is_instr(set, s1[e]))
		e --;
	if (s <= e)
		ret = ft_strdup_se(s1, s, e);
	else
		ret = ft_calloc(1, sizeof(char));
	return (ret);
}
