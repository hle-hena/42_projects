/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:55 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/21 15:57:20 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* int	add_result(int a_sorted, int b_sorted, t_list *sample_a, t_list *sample_b)
{
	int	final_result;
	int	a_after_sorted;
	int	b_after_sorted;

	final_result = 0;
	a_after_sorted = ft_lstsorted(sample_a, &is_increasing);
	b_after_sorted = ft_lstsorted(sample_b, &is_decreasing);
	if ()
} */

int	finish_test(int pos, size_t i)
{
	do_rev_func(get_cmds()[i], get_stack(0), get_stack(1));
	// printf("%*sStack rev\n", pos * 4, "");
	// printf("%*sStack a : ", pos * 4, ""); ft_lstiter(*get_stack(0), &print); printf("\n");
	// printf("%*sStack b : ", pos * 4, ""); ft_lstiter(*get_stack(1), &print); printf("\n");
	if (pos == 0)
		return (i);
	return ((2147483647 / FUTUR_SIGHT - 1) / 10 / pos);
}

void	change_best(size_t *best_res_i, size_t i, int *best_res, int temp_res)
{
	if (temp_res > *best_res)
	{
		*best_res = temp_res;
		*best_res_i = i;
	}
}

int	do_tests(int pos)
{
	size_t	best_res_i;
	int		best_res;
	int		temp_res;
	size_t	i;

	if (pos == FUTUR_SIGHT)
		return (0);
	i = -1;
	best_res_i = -1;
	best_res = -2147483648;
	while (++i < 8)
	{
		// printf("\n%*sDoing [%s]\n", pos * 4, "", get_cmds()[i]);
		temp_res = do_func(get_cmds()[i], get_stack(0), get_stack(1));
		if (temp_res == (-2147483647 / FUTUR_SIGHT + 1) / 10)
			continue ;
		// printf("%*sStack after\n", pos * 4, "");
		// printf("%*sStack a : ", pos * 4, ""); ft_lstiter(*get_stack(0), &print); printf("\n");
		// printf("%*sStack b : ", pos * 4, ""); ft_lstiter(*get_stack(1), &print); printf("\n");
		if (ft_lstsorted(*get_stack(0), &is_increasing) && !(*get_stack(1)))
			return (finish_test(pos, i));
		temp_res += do_tests(pos + 1);
		// printf("%*sResult is %d\n", pos * 4, "", temp_res);
		do_rev_func(get_cmds()[i], get_stack(0), get_stack(1));
		change_best(&best_res_i, i, &best_res, temp_res);
	}
	// printf("%*sBest option is [%s]\n", pos * 4, "", get_cmds()[best_res_i]);
	if (pos == 0)
		return (best_res_i);
	return (best_res);
}
