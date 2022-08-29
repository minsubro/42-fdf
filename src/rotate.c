/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:56:01 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 18:16:41 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, double rot)
{
	int	prev_y;

	prev_y = *y;
	*y = prev_y * cos(rot) + (*z) * sin(rot);
	*z = -prev_y * sin(rot) + (*z) * cos(rot);
}

void	rotate_y(int *x, int *z, double rot)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(rot) + (*z) * sin(rot);
	*z = -prev_x * sin(rot) + (*z) * cos(rot);
}

void	rotate_z(int *x, int *y, double rot)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(rot) - prev_y * sin(rot);
	*y = prev_x * sin(rot) + prev_y * cos(rot);
}

void	ft_rotate(t_xy *xy, t_map *map)
{
	rotate_x(&(xy->y), &(xy->z), map->x_rot);
	rotate_y(&(xy->x), &(xy->z), map->y_rot);
	rotate_z(&(xy->x), &(xy->y), map->z_rot);
}

void	conversion_rotate(t_xy **xy, t_map *map)
{
	int	i;
	int	j;

	i = map->col - 1;
	while (i >= 0)
	{
		j = map->row - 1;
		while (j >= 0)
		{
			ft_rotate(&(xy[i][j]), map);
			j--;
		}
		i--;
	}
}
