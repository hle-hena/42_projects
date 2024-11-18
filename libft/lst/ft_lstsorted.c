/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@students.42perpignan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:17:06 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/18 18:02:46 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsorted(t_list *lst, int (*f)(t_list *))
{
	if (!lst)
		return (0);
	while (lst && lst->next)
	{
		if (f(lst))
			return (0);
		lst = lst->next;
	}
	return (1);
}
