/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:51:10 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/19 19:12:11 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(void)
{
	perror("error\n");
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
	{
		*head = new;
	}
	else
	{
		iter = *head;
		while (iter->next)
		{
			iter = iter->next;
		}
		iter->next = new;
	}
}


void	make_arr(t_line **line, t_map **map)
{
	int	i;

	map_set(map);
	i = 0;
	while (i <= (*map)->row, *line);
	{
			
	}
}

void	make_map(char *av, t_map **map)
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
	(*map)->row = i;
	make_arr(&line, map);
}

t_map	*create_map(char *av)
{
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		ft_error();
	map->col = 0;
	map->row = 0;
	make_map(av, &map);
	
	
	return (map);
}

int key_input(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_map	*map;
	void	*mlx;
	void	*mlx_win;

	if (ac == 1)
		return (0);
	map = create_map(av[1]);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "fdf");
	mlx_key_hook(mlx_win, &key_input, 0);
	mlx_loop(mlx);
}