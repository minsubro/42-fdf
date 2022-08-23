/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:52:48 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/20 15:52:57 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

static int	check(long long num)
{
	if (num > INT_MAX || num < INT_MIN)
		return (1);
	return (0);
}

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
		if (check(n * sign) || !(str[i] >= '0' && str[i] <= '9'))
			ft_error();
		i++;
	}
	return (n * sign);
}