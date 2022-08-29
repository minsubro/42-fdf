/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:05:43 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/20 16:30:10 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	lf_check(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, int idx)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 - idx);
	if (!str)
		ft_error();
	i = 0;
	j = idx;
	while (s1 && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
	{
		str[i++] = s2[j++];
	}
	str[i] = 0;
	if (s1)
		free(s1);
	return (str);
}

char	*ft_make(char **str)
{
	char	*temp;
	int		lf_idx;
	int		i;

	lf_idx = 0;
	i = 0;
	while ((*str)[lf_idx] != '\n' && (*str)[lf_idx] != 0)
		lf_idx++;
	if ((*str)[lf_idx] == '\n')
		lf_idx++;
	temp = (char *)malloc(lf_idx + 1);
	if (!temp)
		ft_error();
	while (i < lf_idx && (*str)[i] != '\n')
	{
		temp[i] = (*str)[i];
		i++;
	}
	temp[i] = 0;
	*str = ft_strjoin(*str, 0, lf_idx);
	return (temp);
}

char	*make_str(t_list_g *lst, int *len)
{
	char	*save;

	save = (char *)malloc(BUFFER_SIZE + 1);
	if (!save)
		ft_error();
	while (1)
	{
		*len = read(lst->fd, save, BUFFER_SIZE);
		if (*len <= 0)
			break ;
		save[*len] = 0;
		lst->str = ft_strjoin(lst->str, save, 0);
		if (lf_check(lst->str))
		{
			free(save);
			return (ft_make(&(lst->str)));
		}
	}
	free(save);
	if (ft_strlen(lst->str))
		return (ft_make(&(lst->str)));
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list_g	*head;
	t_list_g		*fd_list;
	int				len;
	char			*str;

	if (fd == -1)
		ft_error();
	fd_list = find_list(&head, fd);
	if (!fd_list)
		ft_error();
	str = make_str(fd_list, &len);
	if (ft_strlen(fd_list->str) == 0 && len <= 0 && !(str))
	{
		if (fd_list->str)
			free(fd_list->str);
		lstdel(&head, fd);
	}
	return (str);
}
