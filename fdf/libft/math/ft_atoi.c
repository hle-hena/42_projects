/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:40:25 by hle-hena          #+#    #+#             */
/*   Updated: 2025/01/04 22:43:22 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	find_index(char c, const char *base)
{
	int	i;

	i = -1;
	while (base[++i])
		if (c == base[i])
			return (i);
	return (-1);
}

int	ft_atoi_base(const char *str, const char *base)
{
	int	nb;
	int	ind;
	int	len;

	nb = 0;
	len = ft_strlen(base);
	while (ft_isspace(*str))
		str++;
	while (1)
	{
		ind = find_index(*str, base);
		if (ind == -1)
			break ;
		nb = nb * len + ind;
		str++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	return (nb * sign);
}
