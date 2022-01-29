/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:08:34 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/25 13:09:02 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_empty(char **cmd)
{
	int		i;
	char	**ret;

	i = 0;
	ret = ft_calloc(1, sizeof(char *));
	if (!ret)
		return (cmd);
	if (cmd)
	{
		while (cmd[i])
		{
			if (ft_strcmp(cmd[i], ""))
				ret = dptr_join_ptr(ret, cmd[i]);
			else
				free(cmd[i]);
			i++;
		}
	}
	free(cmd);
	return (ret);
}
