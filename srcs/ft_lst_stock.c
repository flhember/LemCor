/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_stock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:38:53 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:46:47 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			verif_size_ant(char *ants)
{
	int		res;
	int		size_ants;

	res = 0;
	size_ants = ft_strlen(ants);
	if (size_ants > 10)
		return (-1);
	if (size_ants == 10)
	{
		if ((res = ft_strcmp(ants, "2147483647")) > 0)
			return (-1);
	}
	if (size_ants == 0 || size_ants == 1)
	{
		if ((ft_strcmp(ants, "") == 0) || ft_strcmp(ants, "0") == 0)
			return (-1);
	}
	return (0);
}

void		add_link_last(t_stock *new, t_stock **lst)
{
	new->next = *lst;
	*lst = new;
}

int			verif_size(t_stock *new, char *x, char *y)
{
	int		size_x;
	int		size_y;
	int		size_new_x;
	int		size_new_y;

	size_x = ft_strlen(x);
	size_y = ft_strlen(y);
	size_new_x = ft_intlen(new->x);
	size_new_y = ft_intlen(new->y);
	if (size_x != size_new_x || size_y != size_new_y)
		return (-1);
	return (0);
}

int			creat_maillon(t_stock **lst, char *name, char *x, char *y)
{
	t_stock	*new;

	new = NULL;
	if (!(new = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (-1);
	if (!(new->room = ft_strdup(name)))
		return (-1);
	if (new->room[0] == '#')
		new->com = 1;
	new->x = ft_atoi(x);
	new->y = ft_atoi(y);
	if (verif_size(new, x, y) == -1)
		return (-1);
	new->next = NULL;
	add_link_last(new, lst);
	return (1);
}
