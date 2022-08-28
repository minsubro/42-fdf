/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:47:25 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 19:39:47 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*make_num(char **str, int size)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * size);
	if (!arr)
		ft_error();
	i = 0;
	while (i < size)
	{
		arr[i] = ft_atoi(str[i]);
		i++;
	}
	return (arr);
}

void	free_all(char **str, t_line *line)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(line->str);
	free(line);
	free(str);
}

void	make_arr(t_line *line, t_map *map)
{
	char	**str;
	t_line	*temp;
	int		size;
	int		i;

	map->map = (int **)malloc(sizeof(int *) * map->col);
	if (!(map->map))
		ft_error();
	i = 0;
	while (i < map->col)
	{
		str = ft_split(line->str, ' ', &size);
		map->map[i] = make_num(str, size);
		temp = line;
		line = line->next;
		free_all(str, temp);
		if (i == 0)
			map->row = size;
		else
		{
			if (map->row != size)
				map_error();
		}
		i++;
	}
}
