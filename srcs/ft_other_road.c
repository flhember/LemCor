/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_road.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:00:08 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:47:10 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		check_nb_road(t_lst **lst)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == -1)
			check = 1;
		i++;
	}
}

static int	pars_pipe_best(t_lst **lst, t_room *tmp, int i, int j)
{
	tmp = (*lst)->tab[j];
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos && (*lst)->tab[j]->road == 0)
		{
			if ((*lst)->tab[j]->start == 0 && (*lst)->tab[j]->end == 0)
				(*lst)->tab[j]->road = (*lst)->nb_road;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	other_road_bis(t_lst **lst, int ds, int i, int j)
{
	while (ds >= 0)
	{
		if (j >= (*lst)->nb_room || ds < 0)
			return (-1);
		if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
		{
			if (ds == 0 && (*lst)->tab[j]->start == 0)
				j++;
			else if ((pars_pipe_best(lst, NULL, i, j)) == 0)
				j++;
			else
			{
				i = j;
				j = 0;
				ds--;
			}
		}
		else
			j++;
	}
	return (0);
}

int			other_road(t_lst **lst, t_data *env, int i)
{
	int		ds;
	int		ret;

	ds = 0;
	ret = 0;
	i = env->end;
	(*lst)->end = i;
	(*lst)->nb_road++;
	(*lst)->ret_bfs = -1;
	while (bfs(env, lst, NULL) >= 0)
	{
		check_nb_road(lst);
		ds = (*lst)->tab[(*lst)->end]->dist;
		if ((*lst)->ret_bfs == 0)
		{
			if ((other_road_bis(lst, --ds, (*lst)->end, 0)) == -1)
				return (0);
			else
				stock_road_other(lst, env);
			(*lst)->nb_road++;
		}
		(*lst)->ret_bfs = -1;
	}
	return (0);
}
