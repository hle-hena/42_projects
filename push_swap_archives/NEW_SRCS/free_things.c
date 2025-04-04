/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:15:37 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/28 09:49:03 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fall_back(int *values, char **temp)
{
	ft_lstclear(get_stack(0), NULL);
	ft_lstclear(get_stack(1), NULL);
	ft_lstclear(get_states(0), &ft_del);
	ft_lstclear(get_states(1), &ft_del);
	ft_del(values);
	if (temp)
		free_temp(temp);
	ft_putendl_fd("Error", 2);
	exit(0);
}

void	free_all(void)
{
	ft_lstclear(get_stack(0), NULL);
	ft_lstclear(get_stack(1), NULL);
	ft_lstclear(get_states(0), &ft_del);
	ft_lstclear(get_states(1), &ft_del);
	ft_del(get_values(0, NULL));
	exit(0);
}

void	free_temp(char **temp)
{
	char	**temptemp;
	
	temptemp = temp;
	while (*temp)
	{
		free(*temp);
		temp++;
	}
	free(temptemp);
}
