/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:43:19 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/29 14:36:05 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_strdup(char *s1)
{
	int		len;
	int		i;
	char	*temp;

	len = ft_strlen(s1);
	temp = (char *)malloc(len + 1);
	i = 0;
	if (temp == NULL)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

int	file_check(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '.')
		{
			if (ft_strcmp(&(name[i]), ".fdf") == 1)
				return (0);
		}
		i++;
	}
	return (1);
}
