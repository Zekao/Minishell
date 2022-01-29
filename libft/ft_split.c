/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 17:22:34 by mbouquet          #+#    #+#             */
/*   Updated: 2021/12/06 14:11:39 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static int	ft_ischar(char a, char c)
{
	if (a == c)
		return (1);
	return (0);
}

static char const	*ft_nextchar(char const *s, char c)
{
	while (*s)
	{
		if (ft_ischar(*s, c))
			return (s);
		s++;
	}
	return (s);
}

static int	ft_size(char const *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (!ft_ischar(*s, c))
		{
			n++;
			s = ft_nextchar(s, c);
		}
		else
			s++;
	}
	return (n);
}

static char	**ft_fct(char **ret, char const *s, char c)
{
	int	n;
	int	j;

	j = 0;
	n = 0;
	while (*s && ft_size(s, c))
	{
		j = 0;
		while (ft_ischar(*s, c) && *s)
			s++;
		while (!ft_ischar(*s, c) && *s)
		{
			s++;
			j++;
		}
		ret[n] = ft_calloc(j + 1, sizeof(char));
		if (!ret[n])
		{
			my_free((void *)ret, n - 1);
			return (NULL);
		}
		ft_memcpy(ret[n++], s - j, j);
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = ft_calloc((ft_size(s, c) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	ret = ft_fct(ret, s, c);
	return (ret);
}
