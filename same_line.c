/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:01:06 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 18:01:29 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	same_x(t_mlx_data *mlx, int sy, int ey, int x)
{
	int	sign;

	sign = 1;
	if (sy > ey)
		sign = -1;
	while (sy != ey)
	{
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, sy, 0xFFFFFF);
		sy += sign;
	}	
}

void	same_y(t_mlx_data *mlx, int sx, int ex, int y)
{
	int	sign;

	sign = 1;
	if (sx > ex)
		sign = -1;
	while (sx != ex)
	{
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, sx, y, 0xFFFFFF);
		sx += sign;
	}	
}
