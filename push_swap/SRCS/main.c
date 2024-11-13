/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:20:29 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/13 17:13:37 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>
void	print(void *content)
{
	printf("[%d] --> ", *(int *)content);
}

int	main(int ac, char **av)
{
	t_list	**stack;
	int		*values;
	size_t	i;

	i = 0;
	stack = get_stack(0);
	values = ft_calloc(ac, sizeof(int));
	while(++i <= (size_t)ac - 1)
	{
		values[i - 1] = av[i][0] - '0';
		printf("YSK\n");
		ft_lstadd_back(stack, ft_lstnew(&values[i - 1]));
	}
	ft_lstiter(*stack, &print);
	ft_sa();
	printf("\n");
	ft_lstiter(*stack, &print);
}