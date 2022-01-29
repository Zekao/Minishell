/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 06:29:13 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 06:31:53 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin(t_main *init)
{
	if (check_cmp(init->cmd[0], "cd"))
		g_exit_code = ft_cd(init->cmd, init->my_env, init->pwd);
	else if (check_cmp(init->cmd[0], "pwd"))
		g_exit_code = ft_pwd(init->pwd);
	else if (check_cmp(init->cmd[0], "env"))
		g_exit_code = ft_env(init->my_env, init->cmd, 2);
	else if (!ft_strcmp(init->cmd[0], "exit"))
	{
		ft_putstr_fd("exit\n", 1);
		if (init->cmd[1] && ft_atoi(init->cmd[1]) <= 255
			&& ft_atoi(init->cmd[1]) >= 0)
			g_exit_code = ft_atoi(init->cmd[1]);
		init->run = 0;
	}
	else if (check_cmp(init->cmd[0], "unset"))
		init->my_env = ft_unset(init->my_env, &init->cmd[1]);
	else if (check_cmp(init->cmd[0], "export"))
		do_export(init);
	else if (check_cmp(init->cmd[0], "echo"))
		g_exit_code = ft_echo(&init->cmd[1], init->my_env);
	else
		exec_command(init);
}

void	exec_command(t_main *init)
{
	g_exit_code = exec_cmd(init->cmd, init->my_env, init->sortie);
	if (g_exit_code != 256)
	{
		init->run = 0;
		g_exit_code = 127;
	}
}

void	init_output(t_main *init, char **env)
{
	init->sortie = -1;
	init->status = 0;
	init->run = 1;
	init->my_env = fill_my_env(env);
}

void	manage_loop(t_main *init)
{
	*init = ft_init1(*init);
	while (init->commandes && init->run)
	{
		init->save[0] = dup(0);
		init->save[1] = dup(1);
		init->cmd = ft_words_to_array(init->commandes->command);
		if (init->cmd)
		{
			*init = ft_init_cmd(*init);
			if (init->cmd && init->cmd[0])
			{
				if (init->size < 2)
					execute_builtin(init);
				else
					exec_command(init);
			}
			close_stuff(*init);
		}
		init->j++;
		init->commandes = init->commandes->next;
	}
	delete_hfile(init->tmp);
	ft_free_commands(init->tmp);
	free(init->ret);
	init->ret = NULL;
}
