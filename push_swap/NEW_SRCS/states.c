/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:12:42 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/27 17:33:15 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_been_visited(int opt)
{
	t_list	**states;
	t_list	**stack;
	size_t	i;

	states = get_states(opt);
	while (*states)
	{
		stack = get_stack(opt);
		i = -1;
		while (((int *)states->content)[++i] != -1 && *stack)
		{
			if (((int *)states->content)[i] != *(int *)(*stack)->content)
				break ;
			*stack = (*stack)->next;
		}
		if (!*stack)
			return (1);
		*states = (*states)->next;
	}
	return (0);
}

void	add_state(int opt)
{
	t_list	**stack;
	t_list	*new_state;
	size_t	i;
	int		*state;

	if (has_been_visited(opt))
		return;
	stack = get_stack(opt);
	state = ft_calloc(ft_lstsize(*stack) + 1, sizeof(int));
	if (!state)
		return ;//should protect
	i = 0;
	while (*stack)
	{
		state[i] = *(int *)(*stack)->content;
		*stack = (*stack)->next;
		i++;
	}
	new_state = ft_lstnew(state);
	if (!new_state)
		return ;//should protect
	ft_lstadd_back(*get_states(opt), new_state);
}
