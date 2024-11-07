/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:52:48 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/07 16:05:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int	ft_is_test(int (*is_something)(int), int index, int arg, size_t expected)
{
	size_t	res;

	res = is_something(arg);
	if ((res > 0) == (expected > 0))
		return (0);
	printf("\033[31mTest %d : KO;\t\tExpected : %ld and got %ld for %c\n\033[0m", index, expected, res, arg);
	return (1);
}

int main_is()
{
	int	i;
	int	test;

	i = -1;
	test = 0;
	printf("\033[33misalpha :\n\033[0m");
	while (++i < 256)
		test += ft_is_test(&ft_isalpha, 1, i, isalpha(i));
	if (test == 0)
		printf("\033[32m1: OK\n\033[0m");
	i = -1;
	test = 0;
	printf("\033[33misdigit :\n\033[0m");
	while (++i < 256)
		test += ft_is_test(&ft_isdigit, 1, i, isdigit(i));
	if (test == 0)
		printf("\033[32m1: OK\n\033[0m");
	i = -1;
	test = 0;
	printf("\033[33misalnum :\n\033[0m");
	while (++i < 256)
		test += ft_is_test(&ft_isalnum, 1, i, isalnum(i));
	if (test == 0)
		printf("\033[32m1: OK\n\033[0m");
	i = -1;
	test = 0;
	printf("\033[33misprint :\n\033[0m");
	while (++i < 256)
		test += ft_is_test(&ft_isprint, 1, i, isprint(i));
	if (test == 0)
		printf("\033[32m1: OK\n\033[0m");
	i = -1;
	test = 0;
	printf("\033[33misascii :\n\033[0m");
	while (++i < 256)
		test += ft_is_test(&ft_isascii, 1, i, isascii(i));
	if (test == 0)
		printf("\033[32m1: OK\n\033[0m");
	return (0);
}
