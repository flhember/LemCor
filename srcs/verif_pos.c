/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 17:04:30 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:52:22 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	check_this(t_stock **lst, int x, int y, int i)
{
	int		j;
	t_stock *cpy;

	j = 0;
	cpy = *lst;
	while (cpy->next)
	{
		if (cpy->pipe == 0 && cpy->com == 0 && j != i && cpy->x == x
				&& cpy->y == y)
			return (-1);
		cpy = cpy->next;
		j++;
	}
	return (0);
}

int			verif_pos(t_stock **lst)
{
	int		i;
	t_stock *cpy;

	i = 0;
	cpy = *lst;
	while (cpy->next)
	{
		if (cpy->pipe == 0 && cpy->com == 0)
		{
			if (check_this(lst, cpy->x, cpy->y, i) == -1)
				return (-1);
		}
		i++;
		cpy = cpy->next;
	}
	return (0);
}
