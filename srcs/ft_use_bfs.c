/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:04:38 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:48:24 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		change_part_road(t_lst **lst, int road, t_data *env)
{
	int		i;
	t_road	*tmp;
	int		size_f;

	i = 0;
	tmp = env->road[road - 1];
	size_f = tmp->size;
	while (i <= size_f)
	{
		if (ft_strcmp((*lst)->tab[env->blk]->name, tmp->name) == 0)
			break ;
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	while (tmp)
	{
		(*lst)->tab[tmp->index]->road = 0;
		tmp = tmp->next;
	}
}

void		change_all(t_lst **lst, int road)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == road)
			(*lst)->tab[i]->road = 0;
		i++;
	}
}

int			verif_pos_blk(t_lst **lst)
{
	t_blk_lst	*tmp;
	t_blk_lst	*new;

	new = NULL;
	tmp = (*lst)->blk;
	while (tmp->next)
	{
		if (tmp->id == (*lst)->pos_blk)
			return (-1);
		tmp = tmp->next;
	}
	if (!(new = (t_blk_lst*)ft_memalloc(sizeof(t_blk_lst))))
		return (-1);
	new->id = (*lst)->pos_blk;
	tmp->next = new;
	return (0);
}

int			creat_lst_blk(t_lst **lst)
{
	if (!((*lst)->blk = (t_blk_lst*)ft_memalloc(sizeof(t_blk_lst))))
		return (-1);
	(*lst)->blk->id = (*lst)->pos_blk_f;
	return (0);
}

int			change_road_bfs(t_lst **lst, int road, t_data *env)
{
	int		flg;
	t_room	*tmp;

	flg = 0;
	tmp = (*lst)->tab[(*lst)->pos_blk_f];
	if (!(*lst)->blk)
	{
		if (creat_lst_blk(lst) == -1)
			return (-1);
	}
	if (verif_pos_blk(lst) == -1)
		return (-1);
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->start == 1)
			flg = 1;
		tmp = tmp->next;
	}
	if (flg == 0)
		change_all(lst, road);
	else
		change_part_road(lst, road, env);
	return (0);
}
