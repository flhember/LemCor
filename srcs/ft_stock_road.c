/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_road.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:59:05 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:47:45 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			find_road(t_lst **lst, t_data *env, int i, t_room *tmp)
{
	env->tmp_pos = env->start;
	while ((*lst)->tab[env->tmp_pos]->end == 0)
	{
		while (tmp)
		{
			if (tmp->pos != env->tmp_pos && (((*lst)->tab[tmp->pos]->road == i
						&& (*lst)->tab[tmp->pos]->print == 0)
						|| (*lst)->tab[tmp->pos]->end == 1))
			{
				(*lst)->tab[tmp->pos]->print = 1;
				env->tmp_pos = tmp->pos;
				stock_it(lst, env, env->tmp_pos, i);
				tmp = NULL;
			}
			else
			{
				tmp = tmp->next;
				if (!tmp)
					return (-1);
			}
		}
		tmp = (*lst)->tab[env->tmp_pos];
	}
	return (0);
}

int			parse_road(t_lst **lst, t_data *env, t_room *tmp)
{
	int		i;

	i = 1;
	while (i <= (*lst)->nb_road)
	{
		tmp = (*lst)->tab[env->start];
		env->road[i - 1]->nb_road = i;
		env->road[i - 1]->name = ft_strdup((*lst)->tab[env->start]->name);
		if (find_road(lst, env, i, tmp) == -1)
		{
			env->road[i - 1]->nb_road = 0;
			ft_strdel(&(env->road[i - 1]->name));
		}
		i++;
	}
	return (0);
}

int			stock_road_other(t_lst **lst, t_data *env)
{
	t_room	*tmp;

	tmp = (*lst)->tab[env->start];
	env->road[(*lst)->nb_road - 1]->nb_road = (*lst)->nb_road;
	env->road[(*lst)->nb_road - 1]->name = ft_strdup(
			(*lst)->tab[env->start]->name);
	find_road(lst, env, (*lst)->nb_road, tmp);
	env->road[(*lst)->nb_road - 1]->size = ft_lstsize_road(
			&env->road[(*lst)->nb_road - 1]);
	reboot_print(lst);
	return (0);
}

int			stock_road(t_lst **lst, t_data *env)
{
	parse_road(lst, env, NULL);
	env->nb_road_f = (*lst)->nb_road;
	return (0);
}

int			creat_road(t_data *env)
{
	int		i;

	i = 0;
	if (!(env->road = ft_memalloc(sizeof(t_road) * (env->nb_pos * 2))))
		return (-1);
	while (i < (env->nb_pos * 2))
	{
		if (!(env->road[i] = ft_memalloc(sizeof(t_road))))
			return (-1);
		i++;
	}
	env->road[env->nb_pos * 2] = 0;
	return (0);
}
