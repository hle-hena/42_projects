/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:15:37 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/21 14:37:33 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fall_back(void)
{
	ft_lstclear(get_stack(0), NULL);
	ft_lstclear(get_stack(1), NULL);
	ft_del(get_values(0, NULL));
	ft_putendl_fd("Error", 2);
	exit(1);
}

void	free_all(void)
{
	ft_lstclear(get_stack(0), NULL);
	ft_lstclear(get_stack(1), NULL);
	ft_del(get_values(0, NULL));
	exit(0);
}
