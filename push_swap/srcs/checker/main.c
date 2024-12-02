/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:02:47 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/02 16:15:43 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

int	is_increasing(t_list *lst)
{
	return ((*(int *)lst->content - *(int *)lst->next->content) < 0);
}

void	feedback(void)
{
	if ((ft_lstsorted(*get_stack(0), &is_increasing) && !*get_stack(1)))
		return (ft_putendl_fd("OK", 1), free_all());
	return (ft_putendl_fd("KO", 1), free_all());
}

int	main(int ac, char **av)
{
	char	buffer[2];
	char	cmd[4];
	int		rv;
	int		i;

	get_values(ac, av);
	while (1)
	{
		i = -1;
		cmd[2] = 0;
		while (1)
		{
			rv = read(0, buffer, 1);
			if (rv == 0 || buffer[0] == '\n' || ++i > 3)
				break ;
			cmd[i] = buffer[0];
		}
		if (rv == 0)
			break ;
		if (i == 4 || !do_func(cmd))
			return (fall_back(get_values(0, 0), NULL), 1);
	}
	return (feedback(), 0);
}
