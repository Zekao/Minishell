/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 11:57:57 by mbouquet          #+#    #+#             */
/*   Updated: 2021/11/23 08:34:03 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_ssize(int n)
{
	unsigned int	nb;
	int				i;

	i = 0;
	if (n == 0)
		return (i + 1);
	if (n < 0)
	{
		nb = -n;
		i++;
	}
	else
		nb = n;
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	nb;
	int				size;

	size = ft_ssize(n);
	nb = n;
	ret = ft_calloc(size + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (n == 0)
	{
		ret[0] = '0';
		return (ret);
	}
	if (n < 0)
	{
		nb = -n;
		ret[0] = '-';
	}
	while (nb)
	{
		ret[--size] = (nb % 10) + '0';
		nb /= 10;
	}
	return (ret);
}
