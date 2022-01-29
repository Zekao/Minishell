/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaugale <emaugale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:06:27 by emaugale          #+#    #+#             */
/*   Updated: 2022/01/22 19:07:49 by emaugale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strtrim(char const *s1, char const set)
{
	char	*ret;
	int		start;
	int		size;

	if (!s1 || !set)
		return (NULL);
	size = ft_strlen(s1);
	start = 0;
	if (s1[start] && s1[start] == set)
		start++;
	if ((size > start) && s1[size - 1] == set)
		size--;
	ret = ft_calloc((size - start + 1), sizeof(char));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, &s1[start], (size - start));
	return (ret);
}

void	free_dptr(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			(*str)[i] = NULL;
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

char	*str_to_lower(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		ret[i] = ft_tolower(str[i]);
		i++;
	}
	return (ret);
}

int	check_cmp(char *s1, char *s2)
{
	char	*tmp;

	tmp = str_to_lower(s1);
	if (!ft_strcmp(s2, tmp))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
