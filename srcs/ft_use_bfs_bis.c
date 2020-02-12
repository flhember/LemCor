/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use_bfs_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:08:57 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:48:32 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		clean_dist(t_lst **lst)
{
	int		i;

	i = 0;
	(*lst)->size_file = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == 0)
			(*lst)->tab[i]->dist = 0;
		i++;
	}
}

void		reboot_nb_road(t_lst **lst)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == -1)
			(*lst)->tab[i]->road = 0;
		i++;
	}
}
