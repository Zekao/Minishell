/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:51:26 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 16:21:53 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_error(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unset: -", 2);
	write(2, &cmd[0][1], 1);
	ft_putstr_fd(": invalid option\nunset: usage: unset [name ...]\n", 2);
	g_exit_code = 2;
}

static int	in_the_env(char **cmd, char *env)
{
	int	len;
	int	j;

	j = 0;
	while (cmd[j])
	{
		len = ft_strlen(cmd[j]);
		if (!ft_strncmp(cmd[j], env, len))
			return (1);
		j++;
	}
	return (0);
}

static int	new_size_env(char **cmd, char **env)
{
	int	i;
	int	size;

	size = size_double_ptr(env);
	i = 0;
	if (env[i])
	{
		while (env[i] && size)
		{
			if (in_the_env(cmd, env[i]))
				size--;
			i++;
		}
	}
	return (size);
}

static void	unset_var(char **cmd, char **env, char ***ret)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!in_the_env(cmd, env[i]))
		{
			(*ret)[j] = ft_strdup(env[i]);
			if (!(*ret)[j])
			{
				free_dptr(ret);
			}
			j++;
		}
		i++;
	}
	g_exit_code = 0;
	free_dptr(&env);
}

char	**ft_unset(char **env, char **cmd)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_calloc(new_size_env(cmd, env) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	if (cmd[i] && env)
	{
		if (cmd[0][0] == '-')
			unset_error(cmd);
		else if ((!ft_isalpha(cmd[0][0]) && !(cmd[0][0] == '_'))
			|| ft_strchr(cmd[0], '='))
			export_display_erreur(cmd[0], 1);
		else
		{
			unset_var(cmd, env, &ret);
			return (ret);
		}
	}
	free_dptr(&ret);
	return (env);
}
