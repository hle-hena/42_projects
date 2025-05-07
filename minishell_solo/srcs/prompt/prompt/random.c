/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hle-hena <hle-hena@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:58:27 by hle-hena          #+#    #+#             */
/*   Updated: 2025/05/07 10:42:39 by hle-hena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


char	**get_config(int config)
{
	static char *configs[13][5] = {
		{NULL, "0x00a1c9", "0x00ffa1", "0x00d0b5", "0xffffff"},
		{NULL, "0x00a1c9", "0x00ffa1", "0x00d0b5", "0x81ffd1"},
		{NULL, "0xcc8eeb", "0xcc8eeb", "0xb649ed", "0xffffff"},
		{NULL, "0xcc8eeb", "0xcc8eeb", "0xb649ed", "0xe0b0ff"},
		{NULL, "0xc0d684", "0xcbeaa6", "0xf3f9d2", "0xffffff"},
		{NULL, "0xc0d684", "0xcbeaa6", "0xf3f9d2", "0xcbeaa6"},
		{NULL, "0x593f62", "0x7b6d8d", "0x6a5678", "0xffffff"},
		{NULL, "0x593f62", "0x7b6d8d", "0x6a5678", "0x907d9d"},
		{NULL, "0x775144", "0xc09891", "0x9c756b", "0xffffff"},
		{NULL, "0x775144", "0xc09891", "0x9c756b", "0xbba48b"},
		{NULL, "0x7e8d85", "0xa2e3c4", "0xabd1be", "0xffffff"},
		{NULL, "0x7e8d85", "0xa2e3c4", "0xabd1be", "0xd1f3e2"},
		{NULL, "0x1e1e1e", "0x1e1e1e", "0x1e1e1e", "0x1e1e1e"}
	};

	return (configs[config]);
}

int	check_arg_config(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]) && str[i])
		i++;
	if (!str[i])
		return (0);
	return (1);
}

int	check_config(char **av)
{
	static int	config = 0;
	char		**colors;

	if (!av[1])
	{
		config = (config + 1) % 13;
		colors = get_config(config);
		if (!set_colors(colors[1], colors[2], colors[3], colors[4]))
			return (0);
		return (1);
	}
	if (!av[2])
	{
		if (check_arg_config(av[1]))
			return (ft_perror(-1, ft_strdup("color: Invalid number given as con\
fig index."), 0), 1);
		config = (ft_atoi(av[1]) - 1) % 13;
		colors = get_config(config);
		if (!set_colors(colors[1], colors[2], colors[3], colors[4]))
			return (0);
		return (1);
	}
	return (-1);
}

int ft_color(char **av)
{
	int			i;
	int			preproc;

	i = 0;
	preproc = check_config(av);
	if (preproc >= 0)
		return (preproc);
	else
	{
		while (++i < 5 && av[i])
		{
			ft_tolower(av[i]);
			if (ft_strncmp(av[i], "0x", 2))
				return (ft_perror(-1, ft_strsjoin((char *[]){"color: Inva\
lid hex ('", av[i], "').", NULL}), 0), 1);
		}
	}
	if (i != 5)
		return (ft_perror(-1, ft_strdup("color: Wrong number of arguments."),
				0), 1);
	return (set_colors(av[1], av[2], av[3], av[4]));
}





int	clean_icmds(void)
{
	t_icmd	*cmds;
	int		nb_cmds;
	int		child;

	cmds = data()->cmds;
	nb_cmds = data()->nb_cmds;
	child = -1;
	while (++child < nb_cmds)
	{
		ft_del((void **)&cmds[child].path);
		if (cmds->define == 2)
			ft_del((void **)&cmds[child].args);
	}
	ft_del((void **)&cmds);
	return (0);
}

void	set_exit_val(int ret_val)
{
	t_list	*pipe;
	t_list	*bin;
	char	*temp;

	pipe = ft_getimp_struct("?", &bin);
	temp = ft_itoa(ret_val);
	if (!temp)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds());
	ft_del((void **)&pipe->content);
	pipe->content = ft_strsjoin((char *[]){"?=", temp, NULL});
	ft_del((void **)&temp);
	if (!pipe->content)
		ft_perror(1, ft_strdup("mini: Internal error: malloc."),
			clean_data() + clean_icmds());
}
