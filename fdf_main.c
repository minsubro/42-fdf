/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:51:10 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/26 21:19:54 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	perror("error\n");
	exit(1);
}

void map_error(void)
{
	perror("Found wrong line length. Exiting.\n");
	exit(1);
}

t_line	*create_line(void)
{
	t_line	*new;
	
	new = (t_line *)malloc(sizeof(t_line));
	if (!new)
		ft_error();
	new->next = NULL;
	new->str = NULL;
	return (new);
}

void lst_add_back(t_line **head, t_line *new)
{
	t_line	*iter;

	if (*head == NULL)
		*head = new;
	else
	{
		iter = *head;
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
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
	size = 0;
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
			break;
		}
		i++;
		lst_add_back(&line, temp);
	}
	map->col = i;
	make_arr(line, map);
}

t_map	*create_map(char *av)
{
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error();
	map->col = 0;
	map->row = 0;
	map->distance = 0;
	map->x_rot = -(M_PI / 6);
	map->y_rot = -(M_PI / 6);
	map->z_rot = 0;
	map->width = 1080;
	map->height = 1920;
	make_map(av, map);
	
	
	return (map);
}

void	position_setting(t_info *info)
{
	int	i;
	int	j;
	int xzero;
	int	yzero;

	xzero = info->xy[info->map->row / 2][info->map->col / 2].x - (info->map->height / 2);
	yzero = info->xy[info->map->row / 2][info->map->row / 2].y - (info->map->width / 2);
	i = 0;
	while (i < info->map->col)
	{
		j = 0;
		while (j < info->map->row)
		{
			info->xy[i][j].x -= xzero;
			info->xy[i][j].y -= yzero;
			j++;
		}
		i++;
	}
	
}

void	re_draw(t_info *info)
{
	coordinate_setting(info->map, info->xy);
	mlx_clear_window(info->mlx->mlx, info->mlx->mlx_win);
	t_conversion_isometric(info->xy, info->map);
	//conversion_isometric(info->xy, info->map);
	position_setting(info);
	print_pixel(info->xy, info->map, info->mlx->mlx, info->mlx->mlx_win);
	draw(info->xy, info->map, info->mlx);
}

int key_input(int keycode, t_info *info)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 123)
		(info->map->y_rot) += 0.05;
	if (keycode == 124)
		(info->map->y_rot) -= 0.05;
	if (keycode == 126)
		(info->map->x_rot) += 0.05;
	if (keycode == 125)
		(info->map->x_rot) -= 0.05;
	if (keycode == 0)
		(info->map->z_rot) += 0.05;
	if (keycode == 1)
		(info->map->z_rot) -= 0.05;
	if (keycode == 69 || keycode == 24)
		(info->map->distance)++;
	if (keycode == 78 || keycode == 27)
		(info->map->distance)--;
	re_draw(info);
	return (0);
}

/// 삭제 대기
void ft_print(t_map *map)
{
	printf("\n\n%d %d\n\n", map->row, map->col);
	for(int i = 0; i<map->col; i++)
	{
		for(int j = 0; j<map->row; j++)
		{
			printf("%d ", map->map[i][j]);	
		}
		printf("\n");
	}
}
///

void find_distance(t_map *map, int win_x, int win_y)
{
	int	distance;

	distance = 0;
	while (1)
	{
		if (map->row * distance > win_x || map->col * distance > win_y)
			break ;
		distance++;
	}
	distance--;
	map->distance = distance;
}

t_coordinate **create_coordinate(t_map *map, int win_x, int win_y)
{
	t_coordinate	**coordinate;
	int				i;

	find_distance(map, win_x, win_y);
	coordinate = (t_coordinate **)malloc(sizeof(t_coordinate) * map->col);
	if (!coordinate)
		ft_error();
	i = 0;
	while (i < map->col)
	{
		coordinate[i] = (t_coordinate *)malloc(sizeof(t_coordinate) * map->row);
		if (!coordinate[i])
			ft_error();
		i++;
	}
	return (coordinate);
}

void coordinate_setting(t_map *map, t_coordinate **coordinate)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->col)
	{
		j = 0;
		while (j < map->row)
		{
			coordinate[i][j].x = j * map->distance;
			coordinate[i][j].y = i * map->distance;
			coordinate[i][j].z = map->map[i][j] * 10;
			j++;
		}
		i++;
	}
}

void coordinate_print(t_map *map, t_coordinate **coordinate)
{
	for(int i = 0; i < map->col; i++)
	{
		for(int j = 0; j < map->row; j++)
		{
			printf("%d,%d,%d ", coordinate[i][j].x, coordinate[i][j].y, coordinate[i][j].z);
		}
		printf("\n");
	}
}

void	ft_isometric(t_coordinate *coordinate)
{
	int	tempx;
	int tempy;

	tempx = coordinate->x;
	tempy = coordinate->y;
	coordinate->x = (tempx - tempy) * cos(M_PI / 6);
	coordinate->y = (tempx + tempy) * sin(M_PI / 6) - coordinate->z;
}

void	conversion_isometric(t_coordinate **coordinate, t_map *map)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < map->col)
	{
		j = 0;
		while (j < map->row)
		{
			ft_isometric(&(coordinate[i][j]));
			j++;
		}
		i++;
	}
}

///
void	rotate_x(int *y, int *z, double rot)
{
	(void)rot;
	int prev_y;
	//double theta;

	prev_y = *y;
	//theta = rot * M_PI / 180;
	*y = prev_y * cos(rot) + (*z) * sin(rot);
	*z = -prev_y * sin(rot) + (*z) * cos(rot); 
}

void	rotate_y(int *x, int *z, double rot)
{
	int		prev_x;
	//double	theta;

	prev_x = *x;
	//theta = rot * M_PI / 180;
	*x = prev_x * cos(rot) + (*z) * sin(rot);
	*z = -prev_x * sin(rot) + (*z) * cos(rot); 
}

void	rotate_z(int *x, int *y, double rot)
{
	int prev_x;
	int prev_y;
	//double theta;

	prev_x = *x;
	prev_y = *y;
	//theta = rot * M_PI / 180;
	*x = prev_x * cos(rot) - prev_y * sin(rot);
	*y = prev_x * sin(rot) + prev_y * cos(rot);
}

void	t_ft_isometric(t_coordinate *xy, t_map *map)
{
	rotate_x(&(xy->y), &(xy->z), map->x_rot);
	rotate_y(&(xy->x), &(xy->z), map->y_rot);
	rotate_z(&(xy->x), &(xy->y), map->z_rot);
}

void t_conversion_isometric(t_coordinate **coordinate, t_map *map)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < map->col)
	{
		j = 0;
		while (j < map->row)
		{
			t_ft_isometric(&(coordinate[i][j]), map);
			j++;
		}
		i++;
	}
}

///

void	print_pixel(t_coordinate **coordinate, t_map *map, void *mlx, void *mlx_win)
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
			mlx_pixel_put(mlx, mlx_win, coordinate[i][j].x, coordinate[i][j].y, 0xFFFFFF);
			j++;
		}
		i++;
	}
}


void	same_x(t_mlx_data *mlx, int sy, int ey, int x)
{
	int sign;

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
	int sign;

	sign = 1;
	if (sx > ex)
		sign = -1;
	while (sx != ex)
	{
		mlx_pixel_put(mlx->mlx, mlx->mlx_win, sx, y, 0xFFFFFF);
		sx += sign;
	}	
}

void	draw_line(t_map *map, t_coordinate s, t_coordinate e, t_mlx_data *mlx)
{
	(void)map;
	int	w;
	int	h;
	int	sign;
	int ysign;
	
	sign = 1;
	if (s.x > e.x)
		sign = -1;
	ysign = 1;
	if (s.y > e.y)
		ysign = -1;
	w = abs(e.x - s.x);
	h = abs(e.y - s.y);

	if (w == 0)
	{
		same_x(mlx, s.y, e.y, s.x);
		return ;
	}
	if (h == 0)
	{
		same_y(mlx, s.x, e.x, s.y);
		return ;
	}

	int k = 2 * h - w;
	int ka = 2 * h;
	int kb = 2 * (h - w);
	
	int x = s.x;
	int y = s.y;
	int inclination = (e.y - s.y) / (e.x - s.x);
	if (abs(inclination) < 1)
	{
		while (x != e.x)
		{
			mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y, 0xFFFFFF);
			if (k < 0)
				k += ka;
			else
			{
				k += kb;
				y += ysign;
			}
			x += sign;
		}
	}
	else
	{
		k = 2 * w - h;
		ka = 2 * w;
		kb = 2 * (w - h);
		while (y != e.y)
		{
			mlx_pixel_put(mlx->mlx, mlx->mlx_win, x, y, 0xFFFFFF);
			if (k < 0)
				k += ka;
			else
			{
				k += kb;
				x += sign;
			}
			y += ysign;
		}
	}
}

void	draw(t_coordinate **coordinate, t_map *map, t_mlx_data *mlx)
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
				draw_line(map, coordinate[i][j], coordinate[i][j + 1], mlx);
			if (i < map->col - 1)
				draw_line(map, coordinate[i][j], coordinate[i + 1][j], mlx);
			j++;
		}
		i++;
	}
}

t_info	*info_init()
{
	t_info	*new_info;

	new_info = (t_info *)malloc(sizeof(t_info));
	if (!new_info)
		ft_error();
	return (new_info);
}

t_mlx_data	*create_mlx()
{
	t_mlx_data	*new;

	new = (t_mlx_data *)malloc(sizeof(t_mlx_data));
	new->mlx = mlx_init();
	new->mlx_win = mlx_new_window(new->mlx, 1920, 1080, "fdf");
	return (new);
}

int main(int ac, char **av)
{
	//t_map			*map;
	//t_coordinate	**coordinate;
	//t_mlx_data		mlx_data;
	t_info			*info;
	

	if (ac == 1)
		return (0);
	info = info_init();
	info->map = create_map(av[1]);
	info->xy = create_coordinate(info->map, 1920, 1080);
	info->map->distance = 30;
	info->mlx = create_mlx();
	coordinate_setting(info->map, info->xy);
	//ft_print(map);
	t_conversion_isometric(info->xy, info->map);
	//conversion_isometric(info->xy, info->map);
	coordinate_print(info->map, info->xy);
	position_setting(info);
	print_pixel(info->xy, info->map, info->mlx->mlx, info->mlx->mlx_win);
	draw(info->xy, info->map, info->mlx);
	mlx_key_hook(info->mlx->mlx_win, &key_input, info);
	mlx_loop(info->mlx->mlx);
}
