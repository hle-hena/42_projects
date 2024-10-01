/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:46:37 by marvin            #+#    #+#             */
/*   Updated: 2024/08/21 12:46:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest_lst;
	t_list	*dest_node;
	void	*dest_content;

	dest_lst = 0;
	while (lst)
	{
		dest_content = f(lst->content);
		if (!dest_content)
		{
			ft_lstclear(&dest_lst, del);
			return (0);
		}
		dest_node = ft_lstnew(dest_content);
		if (!dest_node)
		{
			ft_lstclear(&dest_lst, del);
			return (0);
		}
		ft_lstadd_back(&dest_lst, dest_node);
		lst = lst->next;
	}
	return(dest_lst);
}
