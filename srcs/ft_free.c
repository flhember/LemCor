/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:08:47 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:46:09 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		free_stock(t_stock **lst)
{
	if ((*lst)->next)
		free_stock(&(*lst)->next);
	if ((*lst)->room)
		ft_strdel(&(*lst)->room);
	free(*lst);
}

void		free_lst_tab(t_room **lst)
{
	if ((*lst)->next)
		free_lst_tab(&(*lst)->next);
	ft_strdel(&(*lst)->name);
	free(*lst);
}

void		free_lst_adja(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->next)
			free_lst_tab(&(*lst)->tab[i]);
		else
		{
			ft_strdel(&(*lst)->tab[i]->name);
			free((*lst)->tab[i]);
		}
		i++;
	}
	free((*lst)->tab);
	free(*lst);
}

void		free_road_tab(t_road **lst)
{
	if ((*lst)->next)
		free_road_tab(&(*lst)->next);
	ft_strdel(&(*lst)->name);
	free(*lst);
}

void		free_road_adja(t_data *env, int val)
{
	int		i;

	i = 0;
	if (val != 1)
	{
		while (i < env->nb_pos * 2)
		{
			if (env->road[i]->next)
				free_road_tab(&env->road[i]);
			else
			{
				ft_strdel(&env->road[i]->name);
				free(env->road[i]);
			}
			i++;
		}
		free(env->road);
	}
	else
	{
		if (env->road[0]->next)
			free_road_tab(&env->road[0]);
		free(env->road);
	}
}
