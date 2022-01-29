/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:07:08 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 23:41:41 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		size1;
	int		size2;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	ret = ft_calloc(size1 + size2 + 1, sizeof(char));
	if (!ret)
		return (s1);
	ft_memcpy(ret, s1, size1);
	ft_memcpy(ret + size1, s2, size2);
	if (s1)
		free(s1);
	return (ret);
}

static int	is_equal(char *var, char *env)
{
	char	*ret;
	int		r;

	ret = ft_strjoin(var, "=");
	if (!ret)
		return (0);
	r = ft_strncmp(ret, env, ft_strlen(ret));
	free(ret);
	return (!r);
}

char	*my_getenv(char *var, char **env)
{
	int	i;

	i = 0;
	if (env && env[i] && var)
	{
		while (env[i])
		{
			if (is_equal(var, env[i]))
				return (ft_strchr(env[i], '=') + 1);
			i++;
		}
	}
	return (NULL);
}

void	free_two_dptr(char ***a, char ***b)
{
	if (a)
		free_dptr(a);
	if (b)
		free_dptr(b);
	return ;
}

char	**change_ret(char *str, int start, int i, char **ret)
{
	char	*tmp;

	tmp = ft_substr(str, start, i - start);
	ret = dptr_join_ptr(ret, tmp);
	return (ret);
}
