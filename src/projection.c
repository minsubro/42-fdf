/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:36:23 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 18:15:38 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_isometric(t_xy *xy)
{
	int	tempx;
	int	tempy;

	tempx = xy->x;
	tempy = xy->y;
	xy->x = (tempx - tempy) * cos(M_PI / 6);
	xy->y = (tempx + tempy) * sin(M_PI / 6) - xy->z;
}

void	convert_dimetric(t_xy *xy)
{
	int	tempx;
	int	tempy;

	tempx = xy->x;
	tempy = xy->y;
	xy->x = (tempx - tempy) * cos(0.261799);
	xy->y = (tempx + tempy) * sin(0.261799) - xy->z;
}

void	dimetric_projection(t_info *info)
{
	int	i;
	int	j;

	i = info->map->col - 1;
	while (i >= 0)
	{
		j = info->map->row - 1;
		while (j >= 0)
		{
			convert_dimetric(&(info->xy[i][j]));
			j--;
		}
		i--;
	}
}

void	conversion_isometric(t_xy **xy, t_map *map)
{
	int	i;
	int	j;

	i = map->col - 1;
	while (i >= 0)
	{
		j = map->row - 1;
		while (j >= 0)
		{
			ft_isometric(&(xy[i][j]));
			j--;
		}
		i--;
	}
}
