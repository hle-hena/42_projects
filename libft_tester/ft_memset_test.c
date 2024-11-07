/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:22:28 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/07 16:24:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#incude "tester.h"

void	ft_strlen_test(int index, char *arg, size_t expected)
{
	size_t	res;

	res = ft_memset(arg);
	if (res == expected)
		printf("\033[32m%d : OK\n\033[0m", index);
	else
		printf("\033[31m%d : KO\t\tExpected %ld and got %ld for '%s'\n\033[0m", index, expected, res, arg);
}

int main_strlen()
{
	int	i = -1;
	char	*tests[] = 
	{
		"This is a normal test",
		"This a lonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnng test",
		"",
		NULL
	};
	printf("\033[33mstrlen :\n\033[0m");
	while (tests[++i])
		ft_strlen_test(i, tests[i], strlen(tests[i]));
	return (0);
}
