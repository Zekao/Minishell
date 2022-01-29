/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 06:51:59 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/23 19:52:11 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_spaces(char **cmd)
{
	int		i;
	char	**tmp;
	char	**ret;
	int		j;

	ret = ft_calloc(1, sizeof(char *));
	if (!ret)
		return (cmd);
	i = 0;
	while (cmd[i])
	{
		j = 0;
		tmp = my_split(cmd[i], " \t");
		if (tmp)
		{
			while (tmp[j])
				ret = dptr_join_ptr(ret, tmp[j++]);
			free(tmp);
		}
		i++;
	}
	free_dptr(&cmd);
	return (ret);
}
