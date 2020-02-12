/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_road_use.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 17:12:10 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/12 13:52:15 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		solve_end(t_data *env, int *i, int *j, t_road *nex)
{
	t_road *act;

	act = env->road[*i]->next;
	while (act->next)
	{
		while (*j < env->nb_road_f)
		{
			nex = env->road[*j]->next;
			while (nex->next && find_id(env, *i, *j) == 0)
			{
				if (act->index == nex->index && find_id(env, *i, *j) == 0)
				{
					if (mark_fail(env, *i, *j) == -1)
						return (-1);
				}
				else
					nex = nex->next;
			}
			(*j)++;
		}
		act = act->next;
		*j = *i + 1;
	}
	*j = *i + 1;
	return (0);
}

int		solve_cross(t_data *env, int i, int j, t_road *nex)
{
	while (++i < env->nb_road_f - 1)
	{
		if (solve_end(env, &i, &j, nex) == -1)
			return (-1);
	}
	return (0);
}
