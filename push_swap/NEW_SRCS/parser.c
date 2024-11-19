/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:25 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/19 16:53:02 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_tab(void *tab, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		ft_del(*tab++);
}

void	load_index(int *values, size_t size)
{
	size_t	i;
	size_t	j;
	int		*new;
	int		value;

	i = -1;
	new = ft_calloc(size, sizeof(int));
	if (!new)
		return (0);//should exit
	while (++i < size)
	{
		j = -1;
		value = 0;
		while (++j < i)
		{
			if (values[i] == values[j])
				return (0)//should exit
			if (values[j] > values[i])
				value++;
			else
				values[j]++;
		}
		values[i] = value;
	}
}

int	is_valid_arg(char *arg)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	if (!arg)
		return (-1);
	i += arg[0] == '-';
	while (arg[++i] && ft_isdigit(arg[i]))
	{
		if (arg[0] == '-' && arg[i] - '0' > "-2147483648"[i])
			count++;
		else if (arg[i] - '0' > "2147483647"[i])
			count++;
	}
	if ((i == 11 + (arg[0] == '0') && count > 0) || i != ft_strlen(arg))
		return (0);
	return (1);
}

void	parse_imput(int ac, char **av)
{
	t_list	**stack_a;
	t_list	*new_node;
	size_t	i;
	int		*values;

	values = ft_calloc(ac, sizeof(int));
	if (ac == 1 || !values)
		exit(ft_del(values));
	i = -1;
	while (++i < ac - 1)
	{
		if (!is_valid_arg(ac[i + 1]))
			exit()
			return (0)//should exit
		values[i] = ft_atoi(ac[i + 1]);
	}
	values = load_index(values, ac - 1);
	stack_a = get_stack(0);
	i = -1;
	while (++i < ac - 1)
	{
		new_node = ft_lstnew((void *)&values[i])
		if (!new_node)
			return (0);//should exit
		ft_lstadd_back(stack_a, new_node);
	}
}
