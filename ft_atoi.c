/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:52:48 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/29 15:20:44 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(char *str)
{
	long long	n;
	int			sign;
	int			i;

	n = 0;
	i = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (str[i])
	{
		n = n * 10 + (str[i] - 48);
		if (!(str[i] >= '0' && str[i] <= '9'))
			break ;
		i++;
	}
	return (n * sign);
}
