/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:52:52 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 18:13:05 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_double_putstr(char *s1, char *s2)
{
	ft_putstr_fd(s1, 1);
	ft_putstr_fd(s2, 1);
}

static int	ft_check(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	print_my_env(char **my_env, int aff)
{
	int	i;

	i = 0;
	if (aff == 1)
	{
		if (my_env[i])
			while (my_env[i])
				ft_double_putstr(my_env[i++], "\n");
	}
	else if (aff == 2)
	{
		if (my_env[i])
		{
			while (my_env[i])
			{
				if (ft_check(my_env[i], '=') == 1)
					ft_double_putstr(my_env[i], "\n");
				i++;
			}
		}
	}
}

void	ft_triple_puterror(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

int	ft_env(char **env, char **cmd, int type)
{
	int		size;
	char	c;

	size = size_double_ptr(cmd);
	if (!type)
		type = 1;
	if (env && size <= 1)
	{
		print_my_env(env, type);
		return (0);
	}
	if (cmd[1][0] == '-')
	{
		c = cmd[1][1];
		ft_triple_puterror("env: illegal option -- ", &c, "\nusage: env\n");
	}
	else
	{
		ft_triple_puterror("env: ", cmd[1], ": No such file or directory\n");
		return (127);
	}
	return (1);
}
