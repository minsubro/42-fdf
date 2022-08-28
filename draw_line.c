/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:57:57 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 18:06:39 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	data_init(t_data *data, t_xy s, t_xy e)
{
	(*data).sign = 1;
	if (s.x > e.x)
		(*data).sign = -1;
	(*data).ysign = 1;
	if (s.y > e.y)
		(*data).ysign = -1;
	(*data).w = abs(e.x - s.x);
	(*data).h = abs(e.y - s.y);
	(*data).x = s.x;
	(*data).y = s.y;
}

void	x_line(t_data data, int e_x, t_mlx_data *mlx)
{
	while (data.x != e_x)
	{
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, data.x, data.y, 0xFFFFFF);
		if (data.k < 0)
			data.k += 2 * data.h;
		else
		{
			data.k += 2 * (data.h - data.w);
			data.y += data.ysign;
		}
		data.x += data.sign;
	}
}

void	y_line(t_data data, int e_y, t_mlx_data *mlx)
{
	while (data.y != e_y)
	{
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, data.x, data.y, 0xFFFFFF);
		if (data.k < 0)
			data.k += 2 * data.w;
		else
		{
			data.k += 2 * (data.w - data.h);
			data.x += data.sign;
		}
		data.y += data.ysign;
	}
}

void	draw_line(t_xy s, t_xy e, t_mlx_data *mlx)
{
	t_data	data;

	data_init(&data, s, e);
	if (data.w == 0)
	{
		same_x(mlx, s.y, e.y, s.x);
		return ;
	}
	if (data.h == 0)
	{
		same_y(mlx, s.x, e.x, s.y);
		return ;
	}
	if (abs((e.y - s.y) / (e.x - s.x)) < 1)
	{
		data.k = 2 * data.h - data.w;
		x_line(data, e.x, mlx);
	}
	else
	{
		data.k = 2 * data.w - data.h;
		y_line(data, e.y, mlx);
	}
}

void	draw_map(t_xy **xy, t_map *map, t_mlx_data *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->col)
	{
		j = 0;
		while (j < map->row)
		{
			if (j < map->row - 1)
				draw_line(xy[i][j], xy[i][j + 1], mlx);
			if (i < map->col - 1)
				draw_line(xy[i][j], xy[i + 1][j], mlx);
			j++;
		}
		i++;
	}
}
