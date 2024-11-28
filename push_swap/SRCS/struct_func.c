/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:06:01 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 22:16:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_push	push_compare(t_push p_a, t_push p_b)
{
	int	res_a;
	int	res_b;

	if (p_a.score_a == 0 || p_a.score_b == 0)
		return (p_b);
	if (p_b.score_a == 0 || p_b.score_b == 0)
		return (p_a);
	res_a = ft_abs(p_a.score_a) + ft_abs(p_a.score_b);
	if (p_a.score_a / ft_abs(p_a.score_a) == p_a.score_b / ft_abs(p_a.score_b))
	{
		res_a = ft_abs(p_a.score_a);
		if (ft_abs(p_a.score_a) > ft_abs(p_a.score_b))
			res_a = ft_abs(p_a.score_b);
	}
	res_b = ft_abs(p_b.score_a) + ft_abs(p_b.score_b);
	if (p_b.score_a / ft_abs(p_b.score_a) == p_b.score_b / ft_abs(p_b.score_b))
	{
		res_b = ft_abs(p_b.score_a);
		if (ft_abs(p_b.score_a) > ft_abs(p_b.score_b))
			res_b = ft_abs(p_b.score_b);
	}
	if (res_b > res_a)
		return (p_a);
	return (p_b);
}

void	do_diff(t_push val, int opt)
{
	int	inc_a;
	int	inc_b;

	inc_a = ft_tern_int(val.score_a > 0, -1, 1);
	inc_b = ft_tern_int(val.score_b > 0, -1, 1);
	while (val.score_a)
	{
		do_func_print(get_cmds()[ft_tern_int(opt, ft_tern_int(inc_a == 1, 4, 6)
				, ft_tern_int(inc_a == 1, 5, 7))]);
		val.score_a += inc_a;
	}
	while (val.score_b)
	{
		do_func_print(get_cmds()[ft_tern_int(opt, ft_tern_int(inc_b == 1, 5, 7)
				, ft_tern_int(inc_b == 1, 4, 6))]);
		val.score_b += inc_b;
	}
}

void	do_push(t_push val, int opt)
{
	int	inc;

	if (!val.score_a || !val.score_b)
		return (do_diff(val, opt));
	if (val.score_a / ft_abs(val.score_a) == val.score_b / ft_abs(val.score_b))
	{
		printf("%d - %d\n", val.score_a, val.score_b);
		inc = ft_tern_int(val.score_b > 0, -1, 1);
		while (val.score_a && val.score_b)
		{
			do_func_print(get_cmds()[ft_tern_int(inc == 1, 9, 10)]);
			val.score_a += inc;
			val.score_b += inc;
		}
		printf("%d - %d\n", val.score_a, val.score_b);
		do_diff(val, opt);
	}
	else
		do_diff(val, opt);
}
