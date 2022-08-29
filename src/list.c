/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsukan <minsukan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:50:07 by minsukan          #+#    #+#             */
/*   Updated: 2022/08/28 18:12:28 by minsukan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	lst_add_back(t_line **head, t_line *new)
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
