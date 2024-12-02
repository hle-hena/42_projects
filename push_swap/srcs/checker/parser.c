/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:25 by hle-hena          #+#    #+#             */
/*   Updated: 2024/12/02 15:37:26 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

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
		fall_back(values, NULL);
	i = -1;
	while (++i < ac - 1)
	{
		if (!is_valid_arg(av[i + 1]))
			fall_back(values, NULL);
		values[i] = ft_atoi(av[i + 1]);
	}
	values = load_index(values, ac - 1);
	if (!values)
		fall_back(NULL, NULL);
	return (values);
}

int	*parse_value(char **av)
{
	size_t	i;
	int		*values;
	char	**temp;

	values = ft_calloc(count_words(av[1], ' ') + 1, sizeof(int));
	temp = ft_split(av[1], ' ');
	if (!values || !temp)
		fall_back(values, temp);
	i = -1;
	while (temp[++i])
	{
		if (!is_valid_arg(temp[i]))
			fall_back(values, temp);
		values[i] = ft_atoi(temp[i]);
	}
	values = load_index(values, i);
	free_temp(temp);
	if (!values)
		fall_back(NULL, NULL);
	return (values);
}

int	*parse_imput(size_t ac, char **av)
{
	t_list	**stack_a;
	t_list	*new_node;
	size_t	i;
	int		*values;

	if (ac != 2)
		values = parse_values(ac, av);
	else
	{
		ac = count_words(av[1], ' ') + 1;
		values = parse_value(av);
	}
	stack_a = get_stack(0);
	i = -1;
	while (++i < ac - 1)
	{
		new_node = ft_lstnew((void *)&values[i]);
		if (!new_node)
			fall_back(values, NULL);
		ft_lstadd_back(stack_a, new_node);
	}
	return (values);
}
