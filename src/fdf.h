/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:52:08 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/30 20:37:18 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _USE_MATH_DEFINES

# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../minilibx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map
{
	int		**map;
	int		row;
	int		col;
	int		distance;
	int		width;
	int		height;
	double	x_rot;
	double	y_rot;
	double	z_rot;
	int		movex;
	int		movey;
	double	zvalue;
}			t_map;

typedef struct s_line
{
	char			*str;
	struct s_line	*next;
}					t_line;

typedef struct s_list_g
{
	char			*str;
	int				fd;
	struct s_list_g	*next;
}					t_list_g;

typedef struct s_xy
{
	int	x;
	int	y;
	int	z;
}		t_xy;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*mlx_win;
	void	*image;
}			t_mlx_data;

typedef struct s_data
{
	int	w;
	int	h;
	int	x;
	int	y;
	int	k;
	int	sign;
	int	ysign;
}		t_data;

typedef struct s_image
{
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_image;

typedef struct s_info
{
	t_mlx_data	*mlx;
	t_map		*map;
	t_xy		**xy;
	t_image		*image;
	
	char		*projection;
}					t_info;

void			map_error(void);
void			ft_error(void);
char			*get_next_line(int fd);
t_list_g		*lstnew(int fd);
t_list_g		*find_list(t_list_g **head, int fd);
void			lstdel(t_list_g **head, int fd);
t_list_g		*lstiter(t_list_g *head, int fd);
int				ft_strlen(char *str);
int				lf_check(char *str);
char			*ft_strjoin(char *s1, char *s2, int idx);
char			*ft_make(char **str);
char			*make_str(t_list_g *lst, int *len);
char			**ft_split(char const *s, char c, int *acnt);
int				ft_atoi(char *str);
char			*ft_strdup(char *s1);
void			ft_isometric(t_xy *xy);
void			conversion_isometric(t_xy **xy, t_map *map);
void			rotate_x(int *y, int *z, double rot);
void			rotate_y(int *x, int *z, double rot);
void			rotate_z(int *x, int *y, double rot);
void			conversion_rotate(t_xy **xy, t_map *map);
void			ft_rotate(t_xy *xy, t_map *map);
void			print_pixel(t_xy **xy, t_map *map, void *mlx, void *mlx_win);
void			draw_line(t_xy s, t_xy e, t_mlx_data *mlx, t_image *img);
void			draw_map(t_xy **xy, t_map *map, t_mlx_data *mlx, t_image *image);
void			xy_setting(t_map *map, t_xy **xy);
void			ft_isometric(t_xy *xy);
void			conversion_isometric(t_xy **xy, t_map *map);
void			draw(t_info *info);
void			position_setting(t_info *info);
char			*ft_strdup(char *s1);
void			dimetric_projection(t_info *info);
t_xy			**create_xy(t_map *map, int win_x, int win_y);
t_map			*create_map(char *av);
void			make_map(char *av, t_map *map);
int				*make_num(char **str, int size);
void			make_arr(t_line *line, t_map *map);
t_line			*create_line(void);
void			lst_add_back(t_line **head, t_line *new);
int				key_input(int key, t_info *info);
void			projection_change(int key, t_info *info);
void			move_change(int key, t_info *info);
void			rot_change(int key, t_info *info);
void			same_x(int sy, int ey, int x, t_image *img);
void			same_y(int sx, int ex, int y, t_image *img);
void			find_distance(t_map *map, int win_x, int win_y);
void			position_setting(t_info *info);
void			xy_setting(t_map *map, t_xy **xy);
int				ft_strcmp(char *s1, char *s2);
int				file_check(char *name);
int				ft_exit(t_info *info);
void			img_pix_put(t_image *img, int x, int y, int color);

#endif