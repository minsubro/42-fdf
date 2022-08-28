/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_setting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:00:25 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 19:42:16 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	position_setting(t_info *info)
{
	int	i;
	int	j;
	int	xzero;
	int	yzero;

	xzero = info->xy[info->map->col / 2][info->map->row / 2] \
		.x - (info->map->width / 2);
	yzero = info->xy[info->map->col / 2][info->map->row / 2] \
		.y - (info->map->height / 2);
	i = 0;
	while (i < info->map->col)
	{
		j = 0;
		while (j < info->map->row)
		{
			info->xy[i][j].x -= xzero + info->map->movex;
			info->xy[i][j].y -= yzero + info->map->movey;
			j++;
		}
		i++;
	}
}

void	find_distance(t_map *map, int win_x, int win_y)
{
	int	distance;

	distance = 0;
	while (1)
	{
		if (map->row * distance > win_x / 2 || map->col * distance > win_y / 2)
			break ;
		distance++;
	}
	map->distance = distance;
}
