/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:15:37 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/20 16:50:50 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fall_back(void)
{
	ft_lstclear(get_stack(0), &ft_del)
	ft_lstclear(get_stack(1), &ft_del)
	ft_lstclear(get_cpy(0), &ft_del)
	ft_lstclear(get_cpy(1), &ft_del)
	ft_del(get_values(0, NULL));
	free_tests(get_cmds());
	ft_putendl_fd("Error", 2);
	exit(1);
}