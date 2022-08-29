/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:51:10 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/29 14:31:26 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	write(2, "error\n", 6);
	exit(1);
}

void	map_error(void)
{
	write(2, "Found wrong line length. Exiting.\n", 34);
	exit(1);
}

t_info	*info_init(void)
{
	t_info	*new_info;

	new_info = (t_info *)malloc(sizeof(t_info));
	if (!new_info)
		ft_error();
	return (new_info);
}

t_mlx_data	*create_mlx(void)
{
	t_mlx_data	*new;

	new = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	new->mlx = mlx_init();
	new->mlx_win = mlx_new_window(new->mlx, 1920, 1080, "fdf");
	return (new);
}

int	main(int ac, char **av)
{
	t_info			*info;

	if (ac != 2 || file_check(av[1]))
		ft_error();
	info = info_init();
	info->map = create_map(av[1]);
	info->xy = create_xy(info->map, 1920, 1080);
	info->mlx = create_mlx();
	info->projection = ft_strdup("ISO");
	draw(info);
	mlx_hook(info->mlx->mlx_win, 2, 0, &key_input, info);
	mlx_loop(info->mlx->mlx);
}
