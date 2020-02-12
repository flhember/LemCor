/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verif_block_road.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:59:41 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:49:11 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			block_bad_road(t_lst **lst, int i, int old, int flag)
{
	t_room	*tmp;

	tmp = (*lst)->tab[i];
	(*lst)->tab[i]->road = -2;
	while (flag == 0)
	{
		while (tmp)
		{
			if ((*lst)->tab[tmp->pos]->road == 0
				&& (*lst)->tab[tmp->pos]->dist == (*lst)->tab[i]->dist - 1
				&& (*lst)->tab[tmp->pos]->start == 0)
			{
				old = tmp->pos;
				(*lst)->tab[tmp->pos]->road = -2;
				i = tmp->pos;
			}
			if ((*lst)->tab[tmp->pos]->start == 1)
				return (0);
			tmp = tmp->next;
		}
		if ((*lst)->tab[i]->dist <= (*lst)->tab[old]->dist)
			return (-1);
		tmp = (*lst)->tab[i];
	}
	return (0);
}

int			check_cross_bis(t_lst **lst, t_file **file, int i, t_data *env)
{
	if (verif_back(lst, env->blk, i, 0) == -1)
	{
		block_bad_road(lst, i, 0, 0);
		(*lst)->ret_bfs = 1;
		return (-1);
	}
	if (change_road_bfs(lst, (*lst)->tab[(*lst)->cross]->road, env) == -1)
		return (-1);
	add_file(lst, file, (*lst)->cross, (*lst)->tab[i]->dist + 1);
	(*lst)->cross = 0;
	return (0);
}

int			check_cross(t_lst **lst, t_file **file, int i, t_data *env)
{
	int		cmp;
	t_room	*tmp;

	cmp = 0;
	tmp = (*lst)->tab[i];
	(*lst)->cross = -1;
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->road == -1)
			;
		else if (tmp->pos != i && (*lst)->tab[tmp->pos]->road != 0)
			(*lst)->cross = tmp->pos;
		else if (tmp->pos != i && (*lst)->tab[tmp->pos]->end == 0
				&& (*lst)->tab[tmp->pos]->dist == 0)
			cmp++;
		tmp = tmp->next;
	}
	if (cmp == 0 && (*lst)->cross != -1 && (*lst)->size_file == 1)
	{
		if (check_cross_bis(lst, file, i, env) == -1)
			return (-1);
	}
	return (0);
}

int			check_verif_back(t_lst **lst, int i, int nb, t_room *tmp)
{
	int		flag;

	flag = -1;
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->start == 1)
			flag = 1;
		else if (tmp->pos != i && (*lst)->tab[tmp->pos]->road == 0
				&& (*lst)->tab[tmp->pos]->start == 0
				&& (*lst)->tab[tmp->pos]->end == 0)
		{
			(*lst)->pos_blk_f = tmp->pos;
			(*lst)->cmp++;
		}
		else if (tmp->pos != (*lst)->tmp_pos
			&& ((*lst)->tab[tmp->pos]->road == nb)
			&& (*lst)->tab[tmp->pos]->dist
			== (*lst)->tab[(*lst)->tmp_pos]->dist - 1)
		{
			flag = 0;
			(*lst)->tmp_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (flag);
}

int			verif_back(t_lst **lst, int pos_blk, int i, int flag)
{
	int		nb;
	t_room	*tmp;

	flag = 0;
	(*lst)->cmp = 0;
	(*lst)->tmp_pos = pos_blk;
	tmp = (*lst)->tab[pos_blk];
	nb = (*lst)->tab[pos_blk]->road;
	(*lst)->pos_blk = pos_blk;
	while (flag != 1)
	{
		flag = check_verif_back(lst, i, nb, tmp);
		if ((*lst)->cmp >= 1 && flag == 1)
			return (1);
		else if (flag == 0)
			tmp = (*lst)->tab[(*lst)->tmp_pos];
		else if (flag == -1)
			return (-1);
	}
	return (-1);
}
