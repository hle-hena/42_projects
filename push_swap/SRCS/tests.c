/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:55 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/15 17:25:19 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	test(char **cmds)
{
	t_list	*sample_a;
	t_list	*sample_b;
	int		result;

	result = 0;
	sample_a = get_sample(*get_stack(0));
	sample_b = get_sample(*get_stack(1));
	while (*cmds)
	{
		result += do_func(*cmds, &sample_a, &sample_b);
		cmds++;
	}
	ft_lstclear(&sample_a, NULL);
	ft_lstclear(&sample_b, NULL);
	return (result);
}

char	*init_tests(void)
{
	char	***cmds;
	char	**best_res;
	char	*res;
	int		best_res_val;
	int		temp_res;

	best_res_val = -2147483648;
	cmds = get_cmds();
	while (*cmds)
	{
		temp_res = test(*cmds);
		if (temp_res > best_res_val)
		{
			best_res_val = temp_res;
			best_res = *cmds;
		}
		cmds++;
	}
	res = ft_strdup(best_res[0]);
	return (res);
}
