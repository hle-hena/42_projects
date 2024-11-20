/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:25 by hle-hena          #+#    #+#             */
/*   Updated: 2024/11/20 12:26:49 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*load_index(int *values, size_t size)
{
	size_t	i;
	size_t	j;
	int		*new;
	int		value;

	i = -1;
	new = ft_calloc(size, sizeof(int));
	if (!new)
		return (ft_del(values), NULL);
	while (++i < size)
	{
		j = -1;
		value = 1;
		while (++j < i)
		{
			if (values[i] == values[j])
				return (ft_del(values), ft_del(new), NULL);
			if (values[j] < values[i])
				value++;
			else
				new[j]++;
		}
		new[i] = value;
	}
	return (ft_del(values), new);
}

int	is_valid_arg(char *arg)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	if (!arg)
		return (0);
	i += (arg[0] == '-');
	while (arg[++i] && ft_isdigit(arg[i]))
	{
		if (arg[0] == '-' && arg[i] > "-2147483648"[i])
			count++;
		else if (arg[0] != '-' && arg[i] > "2147483647"[i])
			count++;
	}
	if ((i == 10 + (arg[0] == '-') && count > 0) || i != ft_strlen(arg)
		|| i > 10 + (arg[0] == '-'))
		return (0);
	return (1);
}

int	*parse_values(size_t ac, char **av)
{
	size_t	i;
	int		*values;

	values = ft_calloc(ac, sizeof(int));
	if (ac == 1 || !values)
	{
		ft_del(values);
		exit(1);
	}
	i = -1;
	while (++i < ac - 1)
	{
		if (!is_valid_arg(av[i + 1]))
		{
			ft_del(values);
			exit(1);
		}
		values[i] = ft_atoi(av[i + 1]);
	}
	values = load_index(values, ac - 1);
	if (!values)
		exit(1);
	return (values);
}

int	*parse_imput(size_t ac, char **av)
{
	t_list	**stack_a;
	t_list	*new_node;
	size_t	i;
	int		*values;

	values = parse_values(ac, av);
	stack_a = get_stack(0);
	i = -1;
	while (++i < ac - 1)
	{
		new_node = ft_lstnew((void *)&values[i]);
		if (!new_node)
		{
			ft_del(values);
			ft_lstclear(stack_a, &ft_del);
			exit(1);
		}
		ft_lstadd_back(stack_a, new_node);
	}
	return (values);
}
