/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:55 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 10:41:51 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	finish_test(int pos, size_t i)
{
	do_rev_func(get_cmds()[i], get_stack(0), get_stack(1));
	if (pos == 0)
		return (i);
	return ((2147483647 / FUTUR_SIGHT - 1) / 10 / pos);
}

int	block_back(size_t i, size_t last)
{
	if ((i == 0 || i == 1 || i == 8) && i == last)
		return (do_rev_func(get_cmds()[i], get_stack(0), get_stack(1)), 1);
	else if ((i == 2 || i == 3 || i == 9 || i == 10) && ft_abs(i - last) == 1)
		return (do_rev_func(get_cmds()[i], get_stack(0), get_stack(1)), 1);
	else if ((i >= 4 && i <= 7) && ft_abs(i - last) == 2)
		return (do_rev_func(get_cmds()[i], get_stack(0), get_stack(1)), 1);
	else if ((i == 1 || i == 5 || i == 7) && (ft_abs(i - last) == 4
			|| ft_abs(i - last) == 6))
		return (do_rev_func(get_cmds()[i], get_stack(0), get_stack(1)), 1);
	return (0);
}

void	change_best(size_t *best_res_i, size_t i, int *best_res, int res)
{
	if (res > *best_res)
	{
		*best_res = res;
		*best_res_i = i;
	}
}

void	do_tests_force(size_t last, size_t *best_res_i, int *best_res)
{
	size_t	b_res_i;
	int		b_res;
	int		res;
	size_t	i;

	if (*best_res_i != (size_t)-1)
		return ;
	i = -1;
	b_res_i = -1;
	b_res = -2147483648;
	while (++i < 12)
	{
		res = do_func(get_cmds()[i], get_stack(0), get_stack(1));
		if ((res == (INT_MIN + 1) / 10) || block_back(i, last))
			continue ;
		do_rev_func(get_cmds()[i], get_stack(0), get_stack(1));
		change_best(&b_res_i, i, &b_res, res);
	}
	*best_res_i = b_res_i;
	*best_res = b_res;
}

int	do_tests(int pos, size_t last)
{
	size_t	best_res_i;
	int		best_res;
	int		res;
	size_t	i;

	if (pos == FUTUR_SIGHT)
		return (0);
	i = -1;
	best_res_i = -1;
	best_res = -2147483648;
	while (++i < 12)
	{
		res = do_func(get_cmds()[i], get_stack(0), get_stack(1));
		if ((res == (INT_MIN / FUTUR_SIGHT + 1) / 10) || block_back(i, last)
				|| check_state(i))
			continue ;
		if (ft_lstsorted(*get_stack(0), &is_increasing) && !(*get_stack(1)))
			return (finish_test(pos, i));
		res += do_tests(ft_tern_int(best_res_i >= (2147483647 / FUTUR_SIGHT
				- 1) / FUTUR_SIGHT, FUTUR_SIGHT, pos + 1), i);
		do_rev_func(get_cmds()[i], get_stack(0), get_stack(1));
		change_best(&best_res_i, i, &best_res, res);
	}
	do_tests_force(last, &best_res_i, &best_res);
	return (ft_tern_int(pos == 0, best_res_i, best_res));
}
