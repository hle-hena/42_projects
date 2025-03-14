/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:12:19 by jguaglio          #+#    #+#             */
/*   Updated: 2025/03/14 16:55:53 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_env(char **arg)
{
	t_list	*env;

	if (ft_strslen(arg) > 1)
		return (1);
	env = data()->env;
	ft_printf("%s\n", env->content);
	while (env->next)
	{
		env = env->next;
		if (!ft_strchr(env->content, '='))
			continue ;
		ft_printf("%s\n", env->content);
	}
	return (0);
}
