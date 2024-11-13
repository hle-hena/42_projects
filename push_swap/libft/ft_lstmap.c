/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:46:37 by marvin            #+#    #+#             */
/*   Updated: 2024/11/08 14:01:26 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest_lst;
	t_list	*new_node;
	void	*content;

	dest_lst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			ft_lstclear(&dest_lst, del);
			if (content)
				del(content);
			return (NULL);
		}
		ft_lstadd_back(&dest_lst, new_node);
		lst = lst->next;
	}
	return (dest_lst);
}
