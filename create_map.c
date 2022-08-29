/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:44:27 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/29 14:27:04 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*create_map(char *av)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error();
	map->col = 0;
	map->row = 0;
	map->distance = 5;
	map->x_rot = 0;
	map->y_rot = 0;
	map->z_rot = 0;
	map->width = 1920;
	map->height = 1080;
	map->movex = 0;
	map->movey = 0;
	make_map(av, map);
	return (map);
}

void	make_map(char *av, t_map *map)
{
	t_line	*line;
	t_line	*temp;
	int		i;
	int		fd;

	i = 0;
	line = NULL;
	fd = open(av, O_RDONLY);
	if (fd < 0)
		ft_error();
	while (1)
	{
		temp = create_line();
		temp->str = get_next_line(fd);
		if (!(temp->str))
		{
			free(temp);
			break ;
		}
		i++;
		lst_add_back(&line, temp);
	}
	map->col = i;
	make_arr(line, map);
}
