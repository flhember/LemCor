/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:29:41 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/12 13:46:55 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

size_t		ft_lstsize_stock(t_stock **room)
{
	t_stock *cpy;
	size_t	i;

	i = 0;
	cpy = *room;
	if (cpy == NULL)
		return (0);
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i - 1);
}

size_t		ft_lstsize_room(t_room **room)
{
	t_room	*cpy;
	size_t	i;

	i = 0;
	cpy = *room;
	if (cpy == NULL)
		return (0);
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i - 1);
}

int			ft_lstsize_road(t_road **room)
{
	t_road	*cpy;
	int		i;

	i = 0;
	cpy = *room;
	if (cpy == NULL)
		return (0);
	while (cpy)
	{
		i++;
		cpy = cpy->next;
	}
	return (i - 1);
}
