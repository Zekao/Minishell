/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:18:52 by mbouquet          #+#    #+#             */
/*   Updated: 2022/01/26 12:26:21 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_oneof(char c, const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (c == s[i])
				return (1);
			i++;
		}
	}
	return (0);
}

char	*ft_push_char(char *s, char c)
{
	int		size;
	char	*ret;

	size = 2;
	if (s)
		size += ft_strlen(s);
	ret = ft_calloc(size, sizeof(char));
	if (ret)
	{
		if (s)
			ft_memmove(ret, s, ft_strlen(s) * sizeof(char));
		ret[ft_strlen(ret)] = c;
	}
	if (s)
		free(s);
	return (ret);
}
