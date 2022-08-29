/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:06:26 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/17 12:08:21 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_list_g	*lstnew(int fd)
{
	t_list_g	*new;

	new = (t_list_g *)malloc(sizeof(t_list_g));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->str = NULL;
	return (new);
}

t_list_g	*find_list(t_list_g **head, int fd)
{
	t_list_g	*find;

	find = lstiter(*head, fd);
	if (!find)
	{
		find = lstnew(fd);
		if (!find)
			return (NULL);
		find->next = *head;
		*head = find;
	}
	return (find);
}

void	lstdel(t_list_g **head, int fd)
{
	t_list_g	*save;
	t_list_g	*temp;

	if ((*head)->fd == fd)
	{
		save = (*head)->next;
		free((void *)(*head));
		*head = save;
	}
	else
	{
		save = (*head);
		while (save->next)
		{
			if (save->next->fd == fd)
			{
				temp = save->next;
				save->next = save->next->next;
				free(temp);
				break ;
			}
			save = save->next;
		}
	}
}

t_list_g	*lstiter(t_list_g *head, int fd)
{
	while (head)
	{
		if (head->fd == fd)
			return (head);
		head = head->next;
	}
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str++)
		i++;
	return (i);
}
