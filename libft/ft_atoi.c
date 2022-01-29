/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouquet <mbouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:37:40 by mbouquet          #+#    #+#             */
/*   Updated: 2021/12/27 08:26:37 by mbouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

long long	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	nbr;
	int					signe;

	signe = 1;
	nbr = 0;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > (unsigned long)LONG_MAX && signe > 0)
		nbr = LONG_MAX;
	else if (nbr > (unsigned long)LONG_MAX + 1 && signe < 0)
		nbr = (unsigned long)LONG_MAX + 1;
	return (nbr * signe);
}
