/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:54:55 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/17 17:50:12 by hle-hena         ###   ########.fr       */
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

int	test(char **cmds)
{
	t_list	*sample_a;
	t_list	*sample_b;
	int		result;
	int		temp;
	// int		a_sorted;
	// int		b_sorted;

	result = 0;
	sample_a = get_sample(*get_stack(0));
	sample_b = get_sample(*get_stack(1));
	/* printf("Trying [");
	for (int i = 0; i < FUTUR_SIGHT - 1; i++)
		printf("%s]-[", cmds[i]);
	printf("%s]", cmds[FUTUR_SIGHT - 1]); */
	while (*cmds)
	{
		// a_sorted = ft_lstsorted(sample_a, &is_increasing);
		// b_sorted = ft_lstsorted(sample_b, &is_decreasing);
		temp = do_func(*cmds, &sample_a, &sample_b);
		if (temp)
			result += temp;
		//result += add_result(a_sorted, b_sorted, sample_a, sample_b);
		cmds++;
	}
	ft_lstclear(&sample_a, NULL);
	ft_lstclear(&sample_b, NULL);
	// printf(" and the result is %d\n", result);
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
