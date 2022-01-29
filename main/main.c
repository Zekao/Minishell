/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 23:44:46 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 20:29:16 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

t_main	ft_init1(t_main init)
{
	if (ft_strlen(init.ret))
		add_history(init.ret);
	init.commandes = ft_parse(init.ret);
	init.tmp = init.commandes;
	init.commandes = syntaxe_error(init.commandes);
	init.size = size_commandes(init.commandes);
	ft_heredoc(init.commandes);
	init.j = 0;
	return (init);
}

t_main	ft_init_cmd(t_main init)
{
	init.cmd = replace_arg(init.cmd, init.my_env, g_exit_code);
	init.cmd = split_spaces(init.cmd);
	init.cmd = ft_wildcard(init.cmd);
	init.cmd = remove_empty(init.cmd);
	init.cmd = trim_quote(init.cmd);
	ft_pipe(init.j == 0, !init.commandes->next, &init.sortie);
	init.cmd = ft_redir(init.commandes->redirect, init.cmd);
	return (init);
}

int	minishell(char **env)
{
	t_main	init;

	init_output(&init, env);
	if (!init.my_env)
		return (0);
	while (init.run)
	{
		getcwd(init.pwd, 2048);
		signal_manager();
		init.ret = readline("minishell $> ");
		if (!isatty(0))
			init.run = 0;
		if (!init.ret || !isatty(0))
			exit_assign("exit\n", &init);
		if (init.ret)
			manage_loop(&init);
		while (waitpid(-1, &init.status, 0) != -1)
		{
			if (g_exit_code != 131)
				g_exit_code = WEXITSTATUS(init.status);
		}
	}
	free_dptr(&init.my_env);
	return (g_exit_code);
}

int	main(int ac, char *av[], char *env[])
{
	(void)ac;
	(void)av;
	return (minishell(env));
}
