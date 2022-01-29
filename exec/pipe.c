/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 06:22:14 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 15:06:13 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe(int first, int last, int *sortie)
{
	int	pfd[2];

	if (!first)
	{
		dup2(*sortie, 0);
		close(*sortie);
	}
	if (!last)
	{
		if (pipe(pfd) == -1)
			ft_putstr_fd("Erreur pipe\n", 2);
		else
		{
			dup2(pfd[1], 1);
			close(pfd[1]);
			*sortie = pfd[0];
		}
	}
}
