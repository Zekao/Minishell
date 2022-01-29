/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 06:32:17 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 06:32:24 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_stuff(t_main init)
{
	dup2(init.save[0], 0);
	close(init.save[0]);
	dup2(init.save[1], 1);
	close(init.save[1]);
	free_dptr(&init.cmd);
}

void	do_export(t_main *init)
{
	init->export = ft_export(&init->cmd[1], init->my_env,
			size_double_ptr(init->my_env));
	if (init->export)
	{
		free_dptr(&init->my_env);
		init->my_env = init->export;
	}
}

void	exit_assign(char *str, t_main *init)
{
	ft_putstr_fd(str, 1);
	init->run = 0;
}
