/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   same_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:01:06 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/30 20:36:47 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	same_x(int sy, int ey, int x, t_image *img)
{
	int	sign;

	sign = 1;
	if (sy > ey)
		sign = -1;
	while (sy != ey)
	{
		if ((x >= 0 && x <= 1920) && (sy >= 0 && sy <= 1080))
			img_pix_put(img, x, sy, 16777215);
		sy += sign;
	}	
}

void	same_y(int sx, int ex, int y, t_image *img)
{
	int	sign;

	sign = 1;
	if (sx > ex)
		sign = -1;
	while (sx != ex)
	{
		if ((sx >= 0 && sx <= 1920) && (y >= 0 && y <= 1080))
			img_pix_put(img, sx, y, 16777215);
		sx += sign;
	}	
}
