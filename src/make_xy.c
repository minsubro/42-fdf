/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:01:28 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/29 16:09:33 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_xy	**create_xy(t_map *map, int win_x, int win_y)
{
	t_xy	**xy;
	int		i;

	find_distance(map, win_x, win_y);
	xy = (t_xy **)malloc(sizeof(t_xy) * map->col);
	if (!xy)
		ft_error();
	i = 0;
	while (i < map->col)
	{
		xy[i] = (t_xy *)malloc(sizeof(t_xy) * map->row);
		if (!xy[i])
			ft_error();
		i++;
	}
	return (xy);
}

void	xy_setting(t_map *map, t_xy **xy)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->col)
	{
		j = 0;
		while (j < map->row)
		{
			xy[i][j].x = j * map->distance;
			xy[i][j].y = i * map->distance;
			xy[i][j].z = map->map[i][j] * (map->distance * map->zvalue);
			j++;
		}
		i++;
	}
}
