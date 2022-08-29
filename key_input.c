/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:50:46 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/29 16:14:04 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_change(int key, t_info *info)
{
	if (key == 12)
		info->map->x_rot += 0.01;
	if (key == 13)
		info->map->x_rot -= 0.01;
	if (key == 0)
		info->map->y_rot += 0.01;
	if (key == 1)
		info->map->y_rot -= 0.01;
	if (key == 6)
		info->map->z_rot += 0.01;
	if (key == 7)
		info->map->z_rot -= 0.01;
}

void	move_change(int key, t_info *info)
{
	if (key == 123)
		(info->map->movex) += 3;
	if (key == 124)
		(info->map->movex) -= 3;
	if (key == 125)
		(info->map->movey) -= 3;
	if (key == 126)
		(info->map->movey) += 3;
}

void	projection_change(int key, t_info *info)
{
	if (key == 83)
		info->projection = ft_strdup("ISO");
	if (key == 84)
		info->projection = ft_strdup("Dim");
}

int	key_input(int key, t_info *info)
{
	if (key == 53)
		exit(0);
	else if (key == 12 || key == 13 || key == 0 \
		|| key == 1 || key == 6 || key == 7)
		rot_change(key, info);
	else if (key == 69)
		(info->map->distance)++;
	else if ((key == 78) && info->map->distance > 1)
		(info->map->distance)--;
	else if (key == 27 && info->map->zvalue > 0.2)
		(info->map->zvalue) -= 0.1;
	else if (key == 24)
		(info->map->zvalue) += 0.1;
	else if (key == 123 || key == 124 || key == 125 || key == 126)
		move_change(key, info);
	else if (key == 83 || key == 84)
		projection_change(key, info);
	draw(info);
	return (0);
}
