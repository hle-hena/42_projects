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
		printf("\t\tThis command has no args.\n");
	else
	{
		printf("\t\tThe args are : ");
		while (cmd->args[++i])
			printf("[%s] - ", cmd->args[i]);
		printf("[%s]\n", cmd->args[i]);
	}
	printf("\t\tThe in is [%s]\t\tand the out is [%s]\n", cmd->in, cmd->out);
	if (cmd->here_doc)
		printf("\t\t\tThe heredoc is [%s]\n", cmd->here_doc);
	if (cmd->append)
		printf("\t\t\tThe command should append.\n");
	else
		printf("\t\t\tThe command should not append.\n");
}

void	print_pipeline(t_list *pipeline)
{
	int	i;

	i = -1;
	while (pipeline)
	{
		printf("\tThis is command %i\n", ++i);
		print_cmd((t_cmd *)pipeline->content);
		pipeline = pipeline->next;
	}
}

void	print_blocks(t_list *blocks)
{
	int	i;

	i = -1;
	while (blocks)
	{
		printf("\001\e[1m\002This is the block %i\001\e[0m\002\n", ++i);
		print_pipeline((t_list *)blocks->content);
		blocks = blocks->next;
		if (blocks)
		{
			printf("\001\e[1m\002The separator between the two \
blocks is %s\001\e[1m\002\n", (char *)blocks->content);
			blocks = blocks->next;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*d;
	char	*line;
	char	*before;

	line = NULL;
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
		t_list	*temp;
		char	*err;
		temp = get_cmds(line, &err);
		if (!temp)
		{
			if (!err)
				err = ft_strdup("newline");
			printf("mini: syntax error near unexpected token `%s'\n", err);
			if (temp)
				clear_blocks(temp);
			ft_del(err);
		}
		else
		{
			print_blocks(temp);
			clear_blocks(temp);
			ft_del(err);
		}

		// 	clean_pars(0);
		// }
		line = ft_readline();
	}
	ft_del(before);
	return (ft_putendl_fd("exit\n", 1), clean_data(), 0);
}
