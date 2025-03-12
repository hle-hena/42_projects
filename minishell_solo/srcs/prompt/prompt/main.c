/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:33:09 by jguaglio          #+#    #+#             */
/*   Updated: 2025/01/27 16:33:09 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//penser a clear l'history

char	*ft_readline(void)
{
	char	*prompt;
	char	*line;

	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(0))
		prompt = NULL;
	else
		prompt = get_prompt();
	line = readline(prompt);
	ft_del(prompt);
	signal(SIGINT, any);
	return (line);
}

void	create_env(t_data **d, char **env, char **av, int ac)
{
	(void)av;
	(void)ac;

	(*d)->loc = NULL;
	(*d)->env = NULL;
	(*d)->imp = NULL;
	while (*env)
	{
		ft_lstadd_back(&(*d)->env, ft_lstnew(ft_strdup(*env)));
		env++;
	}
	init_imp(&((*d)->imp));
}

void	init_mini(t_data *d, int ac, char **av, char **env)
{
	char	*temp;

	if (av[1])
		ft_color(av);
	if (isatty(1))
		print_welcome();
	create_env(&d, env, av, ac);
	init_io(d);
	printf("\e[?2004l");
	update_shlvl();
	temp = ft_getenv("PWD");
	if (!temp)
		add_link(&(data()->env), ft_strdup(ft_getimp("PWD")));
	temp = ft_getenv("_");
	if (!temp)
		add_link(&(data()->env), ft_strdup("_=/usr/bin/env"));
}

void	print_cmd(t_cmd *cmd)
{
	int		i;

	i = -1;
	if (!cmd->args)
		printf("This command has no args.\n");
	else
	{
		printf("The args are : ");
		while (cmd->args[++i])
			printf("[%s] - ", cmd->args[i]);
		printf("[%s]\n", cmd->args[i]);
	}
	printf("The in is [%s]\t\tand the out is [%s]\n", cmd->in, cmd->out);
	if (cmd->here_doc)
		printf("\tThe heredoc is [%s]\n", cmd->here_doc);
	if (cmd->append)
		printf("\tThe command should append.\n");
	else
		printf("\tThe command should not append.\n");
}

int	main(int ac, char **av, char **env)
{
	t_data	*d;
	char	*line;
	char	*before;

	before = NULL;
	d = data();
	init_mini(d, ac, av, env);
	line = ft_readline();
	while (line)
	{
		if (!before || ft_strncmp(before, line, ft_strlen(before) + 1) != 0)
			add_history(line);
		free(before);
		before = ft_strdup(line);
		// parseur(line, &d);
		// if (!parseur(line, &d))
		// {
		// 	d->cmd->before = before; //Hugo free;
			// exec(d->cmd->pipe, d->cmd->exe);
		t_cmd	*temp;
		char	*sep;
		int		i = 0;
		while (1)
		{
			temp = get_next_cmd(&line[i], &i, &sep);
			if ((sep && !line[i]) || !temp)
			{
				if (!sep)
					sep = ft_strdup("newline");
				printf("mini: syntax error near unexpected token `%s'\n", sep);
				if (temp)
				{
					int	j = -1;
					while (temp->args[++j])
						ft_del(temp->args[j]);
				}
				ft_del(temp);
				ft_del(sep);
				break;
			}
			print_cmd(temp);
			printf("Sep is [%s]\n", sep);
			if (temp)
			{
				int	j = -1;
				while (temp->args[++j])
					ft_del(temp->args[j]);
			}
			ft_del(temp);
			ft_del(sep);
			if (!line[i])
				break ;
		}
		printf("\n");
		// 	clean_pars(0);
		// }
		line = ft_readline();
	}
	ft_del(before);
	return (ft_putendl_fd("exit\n", 1), clean_data(), 0);
}
