/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:25:56 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/26 11:18:12 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_invalid_option(char **cmd)
{
	ft_putstr_fd("minishell: export: -", 2);
	write(2, &cmd[0][1], 1);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [name[=value] ...]\n", 2);
	g_exit_code = 2;
}

int	index_of_var(char **env, char *var, int place)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, place))
			return (i);
		i++;
	}
	return (-1);
}

static char	**just_export(char **env, int size)
{
	char	**env_ascii;
	char	**ret;
	int		i;

	i = 0;
	env_ascii = ascii_sort(env);
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (env_ascii)
	{
		while (env_ascii[i])
		{
			env_ascii[i] = add_dquotes(env_ascii[i]);
			ret[i] = ft_strjoin("declare -x ", env_ascii[i]);
			if (!ret[i])
				return (free_dptr(&ret), NULL);
			i++;
		}
		free_dptr(&env_ascii);
	}
	return (ret);
}

static char	**ft_export_2(char **cmd, char **env, char **new_var)
{
	int		i;
	int		j;
	int		nb_element;
	char	**ret;

	j = 0;
	i = 0;
	if (cmd[0][0] == '-')
		return (export_invalid_option(cmd), NULL);
	nb_element = create_new_var_dptr(cmd, env, &new_var);
	if ((!new_var && nb_element > 0) || nb_element == -1)
		return (g_exit_code = 1, free_dptr(&cmd), NULL);
	while (j < nb_element || cmd[i])
		if (!export_var(cmd[i++], &j, env, new_var))
			return (NULL);
	ret = dptr_join(env, new_var);
	free_dptr(&new_var);
	if (!ret)
		return (NULL);
	return (ret);
}

char	**ft_export(char **cmd, char **env, int size)
{
	char	**ret;
	char	**new_var;

	new_var = NULL;
	if (!cmd[0])
	{
		ret = just_export(env, size);
		ft_env(ret, cmd, 1);
		return (g_exit_code = 0, free_dptr(&ret), free_dptr(&new_var), NULL);
	}
	else
	{
		ret = ft_export_2(cmd, env, new_var);
		if (!ret)
			return (NULL);
	}
	return (g_exit_code = 0, ret);
}
