/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:00:51 by mbouquet          #+#    #+#             */
/*   Updated: 2021/08/20 17:16:48 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	size;
	unsigned int	i;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	ret = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = (*f)(i, s[i]);
		i++;
	}
	return (ret);
}
