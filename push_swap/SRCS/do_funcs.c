/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:31:34 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/29 12:51:47 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* void	print(void *content)
{
	//////
	int fd = open("out.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	dprintf(fd, "[%d] --> ", *(int *)content);
	close(fd);
} */

int	do_func(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strncmp(cmd, "sa", 4))
		return (ft_s(get_stack(0)), 1);
	else if (!ft_strncmp(cmd, "sb", 4))
		return (ft_s(get_stack(1)), 1);
	else if (!ft_strncmp(cmd, "pa", 4))
		return (ft_p(get_stack(0), get_stack(1)), 1);
	else if (!ft_strncmp(cmd, "pb", 4))
		return (ft_p(get_stack(1), get_stack(0)), 1);
	else if (!ft_strncmp(cmd, "ra", 4))
		return (ft_r(get_stack(0)), 1);
	else if (!ft_strncmp(cmd, "rb", 4))
		return (ft_r(get_stack(1)), 1);
	else if (!ft_strncmp(cmd, "rra", 4))
		return (ft_rr(get_stack(0)), 1);
	else if (!ft_strncmp(cmd, "rrb", 4))
		return (ft_rr(get_stack(1)), 1);
	else if (!ft_strncmp(cmd, "ss", 4))
		return (ft_sab(), 1);
	else if (!ft_strncmp(cmd, "rr", 4))
		return (ft_rab(), 1);
	else if (!ft_strncmp(cmd, "rrr", 4))
		return (ft_rrab(), 1);
	return (0);
}

void	do_func_print(char *cmd)
{
	if (!cmd)
		return ;
	ft_putendl_fd(cmd, 1);
	if (!ft_strncmp(cmd, "sa", 4))
		return (ft_s(get_stack(0)));
	else if (!ft_strncmp(cmd, "sb", 4))
		return (ft_s(get_stack(1)));
	else if (!ft_strncmp(cmd, "pa", 4))
		return (ft_p(get_stack(0), get_stack(1)));
	else if (!ft_strncmp(cmd, "pb", 4))
		return (ft_p(get_stack(1), get_stack(0)));
	else if (!ft_strncmp(cmd, "ra", 4))
		return (ft_r(get_stack(0)));
	else if (!ft_strncmp(cmd, "rb", 4))
		return (ft_r(get_stack(1)));
	else if (!ft_strncmp(cmd, "rra", 4))
		return (ft_rr(get_stack(0)));
	else if (!ft_strncmp(cmd, "rrb", 4))
		return (ft_rr(get_stack(1)));
	else if (!ft_strncmp(cmd, "ss", 4))
		return (ft_sab());
	else if (!ft_strncmp(cmd, "rr", 4))
		return (ft_rab());
	else if (!ft_strncmp(cmd, "rrr", 4))
		return (ft_rrab());
}
