/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:26:10 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/13 15:37:05 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_error_code(int code)
{
	if (code == 1)
		ft_putstr_fd("Something went wrong.", 2);
	else if (code == 2)
		ft_putstr_fd("Wrong argument given to the program.", 2);
	else if (code == 3)
		ft_putstr_fd("Error happened during a malloc.", 2);
	else if (code == 4)
		ft_putstr_fd("Something went wrong during the parsing of the args.", 2);
}

void	ft_perror(int error_code, int clean, char *custom_mess)
{
	if (clean)
		ft_putendl_fd("What even happened there ???", 2);
	else
	{
		ft_putstr_fd("\033[0;31m", 2);
		if (error_code)
			put_error_code(error_code);
		else
			ft_putstr_fd(custom_mess, 2);
		ft_putendl_fd("\033[0;37m", 2);
	}
	exit(0);
}

void	ft_pend_prog(int clean, char *custom_mess)
{
	if (clean)
		ft_perror(0, 1, NULL);
	ft_putstr_fd("\033[0;32m", 2);
	ft_putstr_fd(custom_mess, 2);
	ft_putendl_fd("\033[0;37m", 2);
	exit(0);
}
