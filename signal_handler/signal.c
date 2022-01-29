/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:32:30 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 20:29:28 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\nminishell $> ", 14);
		g_exit_code = 130;
	}
	return ;
}

static void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		g_exit_code = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 1);
		g_exit_code = 131;
	}
	return ;
}

void	signal_manager(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}

void	signal_manager2(void)
{
	signal(SIGINT, signal_handler2);
	signal(SIGQUIT, signal_handler2);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
}
