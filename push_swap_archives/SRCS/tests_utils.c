/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:42:53 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/16 12:33:03 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_tests(char ***tests)
{
	char	***temp;

	temp = tests;
	while (*tests)
	{
		free(*tests);
		tests++;
	}
	free(temp);
}

void	generate_tests(char ****tests, char **cmds, size_t cmd_i, size_t start)
{
	size_t	i;
	size_t	j;
	size_t	nb_cmd;

	if (cmd_i == FUTUR_SIGHT)
		return ;
	nb_cmd = ft_pow(8, (FUTUR_SIGHT - 1) - cmd_i);
	j = -1;
	while (++j < 8)
	{
		i = -1;
		while (++i < nb_cmd)
			(*tests)[i + j * nb_cmd + start][cmd_i] = cmds[j];
		generate_tests(tests, cmds, cmd_i + 1, start + j * nb_cmd);
	}
}

//calloc is not protected
char	***create_tests(char **cmds)
{
	char	***tests;
	size_t	pow_val;
	size_t	i;

	pow_val = ft_pow(8, FUTUR_SIGHT);
	tests = ft_calloc(pow_val + 1, sizeof(char **));
	i = -1;
	while (++i < pow_val)
	{
		tests[i] = ft_calloc(FUTUR_SIGHT + 1, sizeof(char *));
	}
	tests[i] = NULL;
	generate_tests(&tests, cmds, 0, 0);
	return (tests);
}

char	***get_cmds(void)
{
	static char	*funcs[9] = {"sa", "sb", "pb", "pa", "ra", "rb", "rra", "rrb",
		/* "ss", "rr", "rrr", */ NULL};
	static char	***tests;

	if (!tests)
		tests = create_tests(funcs);
	return (tests);
}

// tests[test_index] is not protected
//shit its recursive ... gl
/* char	***create_tests(char **cmds)
{
	char	***tests;
	size_t	i;
	size_t	j;
	size_t	test_index;

	tests = ft_calloc(ft_pow(8, FUTUR_SIGHT) + 1, sizeof(char **));
	if (!tests)
		return (NULL);
	test_index = 0;
	i = -1;
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			tests[test_index] = ft_calloc(FUTUR_SIGHT + 1, sizeof(char *));
			tests[test_index][0] = cmds[i];
			tests[test_index][1] = cmds[j];
			tests[test_index][2] = NULL;
			test_index++;
		}
	}
	tests[test_index] = NULL;
	return (tests);
} */
