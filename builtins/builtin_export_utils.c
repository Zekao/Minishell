/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:11:32 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 20:21:54 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ascii_sort(char **env)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	ret = fill_my_env(env);
	if (!ret)
		return (NULL);
	while (ret[i])
	{
		j = i;
		while (ret[j])
		{
			if (ft_strncmp(ret[i], ret[j], ft_strlen(ret[j])) > 0)
			{
				tmp = ret[i];
				ret[i] = ret[j];
				ret[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

void	export_display_erreur(char *cmd, int nb)
{
	ft_putstr_fd("minishell: ", 2);
	if (nb == 0)
		ft_putstr_fd("export: `", 2);
	if (nb == 1)
		ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
}

int	check_conform(char **cmd, char **env)
{
	char	*place;
	int		i;
	int		add_new;

	add_new = 0;
	i = 0;
	if (cmd[i])
	{
		while (cmd[i])
		{
			place = ft_strchr(cmd[i], '=');
			if (!place)
				return (1);
			if (!ft_isalpha(cmd[i][0]) && !(cmd[i][0] == '_'))
				return (export_display_erreur(cmd[i], 0), -1);
			else
			{
				if (place && index_of_var(env, cmd[i], place - cmd[i]) == -1)
					add_new++;
			}
			i++;
		}
	}
	return (add_new);
}

char	*what_var(char **env, char *cmd, int *j, char **new_var)
{
	char	*ret;
	char	*place;

	ret = NULL;
	place = ft_strchr(cmd, '=');
	if (index_of_var(env, cmd, place - cmd) == -1)
	{
		ret = add_var(cmd, &new_var[*j], *j);
		if (!ret)
			return (NULL);
		(*j)++;
	}
	else
	{
		ret = change_env(cmd, env, place);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

char	*change_env(char *cmd, char **env, char *place)
{
	char	*tmp;
	int		index;

	tmp = 0;
	index = 0;
	if (cmd[0] != '_' || cmd[1] != '=')
	{
		index = index_of_var(env, cmd, place - cmd);
		tmp = env[index];
		env[index] = ft_strdup(cmd);
		free(tmp);
	}
	return (env[index]);
}
