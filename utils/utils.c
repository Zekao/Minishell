/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:03:27 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/25 23:43:03 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_double_ptr(char **arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	while (arg[i])
		i++;
	return (i);
}

int	in_the_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	**my_split(char *str, char *c)
{
	char	**ret;
	int		start;
	int		i;

	ret = NULL;
	start = 0;
	i = 0;
	while (str[i])
	{
		if (in_the_str(c, str[i]) && !unclosed_quotes(str + start, i - start))
		{
			if (i != start)
			{
				ret = change_ret(str, start, i, ret);
			}
			start = i + 1;
		}
		i++;
	}
	if (i != start)
	{
		ret = change_ret(str, start, i, ret);
	}
	return (ret);
}

char	**dptr_join(char **dptr1, char **dptr2)
{
	char	**ret;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	len1 = size_double_ptr(dptr1);
	len2 = size_double_ptr(dptr2);
	ret = ft_calloc(1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < len1)
	{
		ret = dptr_join_ptr(ret, ft_strdup(dptr1[i]));
		i++;
	}
	i = 0;
	while (i < len2)
	{
		ret = dptr_join_ptr(ret, ft_strdup(dptr2[i]));
		i++;
	}
	return (ret);
}

char	**dptr_join_ptr(char **dptr1, char *str)
{
	char	**ret;
	int		size;

	size = size_double_ptr(dptr1);
	if (str)
		size += 1;
	ret = ft_calloc(size + 1, sizeof(char *));
	if (!ret)
		return (dptr1);
	if (dptr1)
	{
		ft_memmove(ret, dptr1, size_double_ptr(dptr1) * sizeof(char *));
		free(dptr1);
	}
	if (str)
		ft_memmove(ret + size_double_ptr(ret), &str, sizeof(char *));
	return (ret);
}
