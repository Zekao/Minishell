/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:54:07 by mbouquet          #+#    #+#             */
/*   Updated: 2021/11/22 14:00:42 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;

	ret = ft_calloc((ft_strlen(s1) + 1), sizeof(char));
	if (!ret)
		return (NULL);
	ret = ft_memcpy(ret, s1, ft_strlen(s1));
	return (ret);
}
