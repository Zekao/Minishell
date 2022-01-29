/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:12:54 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/28 10:09:32 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fill_my_env(char **env)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = size_double_ptr(env);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
		{
			free_dptr(&ret);
			return (env);
		}
		i++;
	}
	return (ret);
}
