/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 15:40:02 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/30 20:23:48 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (1)
	{
		if (s1[i] != s2[i])
			return (0);
		if (s1[i] == 0 && s2[i] == 0)
			break ;
		i++;
	}
	return (1);
}

void	img_reset(t_info *info)
{
	free(info->mlx->image);
	free(info->image->addr);
	info->mlx->image = mlx_new_image(info->mlx->mlx, 1920, 1080);
	info->image->addr = mlx_get_data_addr(info->mlx->image, \
		&(info->image->bpp), &(info->image->line_len), &(info->image->endian));
}

void	draw(t_info *info)
{
	mlx_clear_window(info->mlx->mlx, info->mlx->mlx_win);
	img_reset(info);
	mlx_string_put(info->mlx->mlx, info->mlx->mlx_win, \
		20, 20, 0xFFFFFF, info->projection);
	xy_setting(info->map, info->xy);
	conversion_rotate(info->xy, info->map);
	if (ft_strcmp(info->projection, "ISO") == 1)
		conversion_isometric(info->xy, info->map);
	else
		dimetric_projection(info);
	position_setting(info);
	draw_map(info->xy, info->map, info->mlx, info->image);
	mlx_put_image_to_window(info->mlx->mlx, info->mlx->mlx_win, info->mlx->image, 0, 0);
}
