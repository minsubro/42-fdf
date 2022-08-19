/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:52:08 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/19 19:12:18 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "minilibx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_map
{
	int	**map;
	int row;
	int col;
}	t_map;

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

void		ft_error(void);
char		*get_next_line(int fd);
t_list_g	*lstnew(int fd);
t_list_g	*find_list(t_list_g **head, int fd);
void		lstdel(t_list_g **head, int fd);
t_list_g	*lstiter(t_list_g *head, int fd);
int			ft_strlen(char *str);
int			lf_check(char *str);
char		*ft_strjoin(char *s1, char *s2, int idx);
char		*ft_make(char **str);
char		*make_str(t_list_g *lst, int *len);

#endif