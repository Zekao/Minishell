/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 06:38:05 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/22 06:42:33 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_two_elem(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void	ft_out(char *str, int i)
{
	ft_putstr_fd(str, 2);
	exit(i);
}

char	*ft_free_ret(char **str)
{
	free_dptr(&str);
	return (0);
}

char	*ft_free_ret2(char **str, char *bin)
{
	free_dptr(&str);
	return (bin);
}
