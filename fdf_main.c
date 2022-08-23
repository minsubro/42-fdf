/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:51:10 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/22 22:05:27 by minsukan         ###   ########.fr       */
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
	map->x_rot = 30;
	map->y_rot = 30;
	map->z_rot = 0;
	make_map(av, map);
	
	
	return (map);
}

int key_input(int keycode)
{
	if (keycode == 53)
		exit(0);
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

void coordinate_setting(t_map *map, t_coordinate ** coordinate)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->col)
	{
		j = 0;
		while (j < map->row)
		{
			coordinate[i][j].x = j * map->distance + 300;
			coordinate[i][j].y = i * map->distance + 200;
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
void	rotate_x(int *y, int *z, int rot)
{
	(void)rot;
	int prev_y;
	double theta;

	rot = 30;
	prev_y = *y;
	theta = 30 * M_PI / 180;
	*y = (prev_y * cos(theta)) - (*z * sin(theta));
	*z = (-prev_y * sin(theta)) + (*z * cos(theta)); 
}

void	rotate_y(int *x, int *z, int rot)
{
	(void)rot;
	int		prev_x;
	double	theta;

	rot = 30 * M_PI / 180;
	prev_x = *x;
	theta = 30 * M_PI / 180;
	*x = (prev_x * cos(theta)) + (*z * sin(theta));
	*z = (-prev_x * sin(theta)) + (*z * cos(theta)); 
}

void	rotate_z(int *x, int *y, int rot)
{
	(void)rot;
	int prev_x;
	int prev_y;
	double theta;

	prev_x = *x;
	prev_y = *y;
	theta = 0 * M_PI / 180;
	*x = prev_x * cos(theta) - prev_y * sin(theta);
	*y = prev_x * sin(theta) + prev_y * cos(theta);
}

void	t_ft_isometric(t_coordinate *xy, t_map *map)
{
	printf("변경전 = %d %d %d\n", xy->x, xy->y, xy->z);
	rotate_x(&(xy->y), &(xy->z), map->x_rot);
	rotate_y(&(xy->x), &(xy->z), map->y_rot);
	rotate_z(&(xy->x), &(xy->y), map->z_rot);
	printf("변경후 = %d %d %d\n", xy->x, xy->y, xy->z);
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


void	draw_line(t_map *map, t_coordinate s, t_coordinate e, t_mlx_data mlx)
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
			mlx_pixel_put(mlx.mlx, mlx.mlx_win, x, y, 0xFFFFFF);
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
			mlx_pixel_put(mlx.mlx, mlx.mlx_win, x, y, 0xFFFFFF);
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

void	draw(t_coordinate **coordinate, t_map *map, t_mlx_data mlx)
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

int main(int ac, char **av)
{
	t_map	*map;
	t_coordinate **coordinate;
	t_mlx_data	mlx_data;

	if (ac == 1)
		return (0);
	map = create_map(av[1]);
	coordinate = create_coordinate(map, 1920, 1080);
	map->distance = 10;
	coordinate_setting(map, coordinate);
	//ft_print(map);
	mlx_data.mlx = mlx_init();
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, 1920, 1080, "fdf");
	//t_conversion_isometric(coordinate, map);
	conversion_isometric(coordinate, map);
	coordinate_print(map, coordinate);
	print_pixel(coordinate, map, mlx_data.mlx, mlx_data.mlx_win);
	draw(coordinate, map, mlx_data);
	mlx_key_hook(mlx_data.mlx_win, &key_input, 0);
	mlx_loop(mlx_data.mlx);
}
