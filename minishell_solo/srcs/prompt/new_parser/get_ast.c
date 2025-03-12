/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.fr>  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-05 15:02:15 by hle-hena          #+#    #+#             */
/*   Updated: 2025-03-05 15:02:15 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_next_sep(t_list *blocks, char *sep)
{
	blocks = blocks->next->next;
	if (!blocks)
		return (1);
	if (ft_strncmp(blocks->content, sep, 3) == 0)
		return (1);
	return (0);
}

t_bt	*build_subtree(t_list *blocks, int *move)
{
	t_bt	*subtree;
	char	*sep;

	*move = 0;
	subtree = create_bt_node(blocks->content);
	(*move)++;
	blocks = blocks->next;
	if (!blocks)
		return (subtree);
	sep = blocks->content;
	while (blocks)
	{
		set_parent(create_bt_node(blocks->content), subtree, 1);
		(*move)++;
		subtree = subtree->parent;
		if (!is_next_sep(blocks, sep))
			break ;
		blocks = blocks->next;
		set_parent(subtree, create_bt_node(blocks->content), 0);
		(*move)++;
		blocks = blocks->next;
	}
	return (subtree);
}

t_bt	*build_tree(t_list *blocks)
{
	t_bt	*tree;
	t_bt	*subtree;
	int		move;

	tree = build_subtree(blocks, &move);
	while (--move)
		blocks = blocks->next;
	while (blocks)
	{
		subtree = build_subtree(blocks, &move);
		while (--move)
			blocks = blocks->next;
		set_parent(tree, subtree, 0);
	}
	return (tree);
}

t_bt	*get_ast(char *line)
{
	t_list	*blocks;

	if (!line)
		return (NULL);
	//Do a check for unclosed quotes and parenthesis here.
	blocks = ft_lstrev(get_blocks(line));
	//Do a check that blocks has everything, and not separator one after another.
	if (ft_lstsize(blocks) == 1)
		return (create_bt_node(blocks->content));
	return (build_tree(blocks));

}
