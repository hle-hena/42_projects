/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:18:52 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/06 14:55:50 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>

void	ft_strlen_test(int index, char *arg, size_t expected)
{
	size_t	res;

	res = ft_strlen(arg);
	if (res == expected)
		printf("\033[32mTest %d : OK\n\033[0m", index);
	else
		printf("\033[31mTest %d : KO\n\033[0m", index);
}

int main()
{
	int	i = -1;
	char	*tests[] = 
	{
		"This is a normal test",
		"This a lonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnng test",
		"",
		NULL
	};
	int	expects[] =
	{
		21,
		104,
		0,
		0
	};
	while (tests[++i])
		ft_strlen_test(i, tests[i], expects[i]);
	return (0);
}