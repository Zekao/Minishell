/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:18:16 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 11:19:32 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_new_var_dptr(char **cmd, char **env, char ***new_var)
{
	int	nb_element;

	nb_element = check_conform(cmd, env);
	if (nb_element == -1)
		return (-1);
	if (nb_element)
		*new_var = ft_calloc(nb_element + 1, sizeof(char *));
	return (nb_element);
}

char	*add_var(char *cmd, char **new_var, int j)
{
	(void)j;
	*new_var = ft_strdup(cmd);
	if (!*new_var)
	{
		free_dptr(&new_var);
		return (NULL);
	}
	return (*new_var);
}

char	*export_var(char *cmd, int *j, char **env, char **new_var)
{
	char	*place;
	char	*ret;

	ret = NULL;
	if (ft_isalpha(cmd[0]) || (cmd[0] == '_'))
	{
		place = ft_strchr(cmd, '=');
		if (!place && index_of_var(env, cmd, ft_strlen(cmd)) == -1)
		{
			ret = add_var(cmd, &new_var[*j], *j);
			if (!ret)
				return (NULL);
			(*j)++;
		}
		if (place)
			ret = what_var(env, cmd, j, new_var);
	}
	return (ret);
}

char	*add_dquotes(char *env)
{
	char	*ret;
	char	*place;

	place = ft_strchr(env, '=');
	if (place)
	{
		ret = ft_substr(env, 0, (place - env) + 1);
		ret = my_strjoin(ret, "\"");
		ret = my_strjoin(ret, place + 1);
		ret = my_strjoin(ret, "\"");
		free(env);
		return (ret);
	}
	return (env);
}
