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
	ft_del((void **)&prompt);
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

void	print_cmd(t_cmd *cmd, int depth)
{
	int		i;

	i = -1;
	if (cmd->subshell)
		printf("%*sThis is a subshell\n", depth * 4 + 4, "");
	if (!cmd->args)
		printf("%*sThis command has no args.\n", depth * 4 + 4, "");
	else
	{
		printf("%*s", depth * 4 + 4, "");
		while (cmd->args[++i])
			printf("[%s] - ", cmd->args[i]);
		printf("[%s]\n", cmd->args[i]);
	}
	if (cmd->here_doc)
		printf("%*sheredoc: %s\t\t", depth * 4 + 4, "", cmd->here_doc);
	else
		printf("%*sin: %s\t\t", depth * 4 + 4, "", cmd->in);
	if (cmd->append)
		printf("append: %s\n", cmd->out);
	else
		printf("out: %s\n", cmd->out);
}

void	print_pipeline(t_list *pipeline, int depth)
{
	int	i;

	i = -1;
	while (pipeline)
	{
		printf("%*sThis is command %i\n%*s{\n", depth * 4, "", ++i, depth * 4, "");
		print_cmd((t_cmd *)pipeline->content, depth);
		pipeline = pipeline->next;
		printf("%*s}\n", depth * 4, "");
	}
}

void	print_ast_recursive(t_bt *node, int depth)
{
	if (!node)
		return;
	if (!node->left && !node->right)
		print_pipeline((t_list *)node->content, depth);
	else
		printf("%*s%s\n", depth * 4, "", (char *)node->content);
	if (node->left || node->right)
		printf("%*s{\n", depth * 4, "");
	if (node->left)
		print_ast_recursive(node->left, depth + 1);
	if (node->right)
		print_ast_recursive(node->right, depth + 1);
	if (node->left || node->right)
		printf("%*s}\n", depth * 4, "");
}

void	print_ast(t_bt *root)
{
	if (!root)
	{
		printf("AST is empty.\n");
		return;
	}
	printf("Abstract Syntax Tree:\n");
	print_ast_recursive(root, 1);
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
		t_bt	*temp;
		temp = get_ast(line);
		if (temp)
		{
			run_ast(temp);
			print_ast(temp);
		}
		clear_tree(temp);
		line = ft_readline();
	}
	ft_del((void **)&before);
	return (ft_putendl_fd("exit", 1), clean_data(), 0);
}
