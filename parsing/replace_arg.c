/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 18:59:45 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 15:08:15 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fct_replace_arg(char **tmp, int exit_code, char *place, char *start)
{
	char	*tmp2;
	int		k;

	tmp2 = ft_substr(start, 0, place - start);
	*tmp = my_strjoin(*tmp, tmp2);
	free (tmp2);
	k = 1;
	if (place[k] == '?')
	{
		tmp2 = ft_itoa(exit_code);
		*tmp = my_strjoin(*tmp, tmp2);
		free(tmp2);
		k++;
	}
	return (k);
}

static void	fct2_replace_arg(int *k, char *place, char **tmp, char **env)
{
	char	*sub;

	if (place[*k] != '?')
	{
		if ((ft_isalpha(place[*k]) || place[*k] == '_'))
			(*k)++;
		while ((ft_isalnum(place[*k]) || place[*k] == '_'))
			(*k)++;
		sub = ft_substr(place, 1, *k - 1);
		if ((!sub || !ft_strlen(sub))
			&& (place[*k] == ' ' || place[*k] == '\0'))
			*tmp = my_strjoin(*tmp, "$");
		else
			*tmp = my_strjoin(*tmp, my_getenv(sub, env));
		free(sub);
	}
}

static void	without_var(char *start, char **tmp, char **cmd, int *i)
{
	char	*s2;

	s2 = ft_substr(start, 0, ft_strlen(start));
	*tmp = my_strjoin(*tmp, s2);
	free(s2);
	if (*tmp)
	{
		free(cmd[*i]);
		cmd[*i] = *tmp;
	}
	(*i)++;
}

static void	fill_var(char **tmp, char **start, char **place, char *cmd)
{
	*tmp = NULL;
	*start = cmd;
	*place = ft_strchr(cmd, '$');
}

char	**replace_arg(char **cmd, char **env, int exit_code)
{
	char	*place;
	char	*tmp;
	char	*start;
	int		k;
	int		i;

	i = 0;
	while (cmd[i])
	{
		fill_var(&tmp, &start, &place, cmd[i]);
		while (place)
		{
			if (unclosed_simple_quote(cmd[i], place - cmd[i]))
				place = ft_strchr(place + 1, '$');
			else
			{
				k = fct_replace_arg(&tmp, exit_code, place, start);
				fct2_replace_arg(&k, place, &tmp, env);
				start = place + k;
				place = ft_strchr(place + 1, '$');
			}
		}
		without_var(start, &tmp, cmd, &i);
	}
	return (cmd);
}
