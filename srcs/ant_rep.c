/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_rep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:20:19 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 16:36:36 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

 int		treat_better(t_data *env, const int limit, const int id)
{
	int i;
	int total;
	int nb;

	total = 0;
	i = 0;
	nb = 0;
	while (i < env->road_sol[id + 1][0] && i < limit)
	{
		total = total + ((env->nb_ants / limit) +
				env->road[env->road_sol[id][i]]->size);
		i++;
	}
	total = total / limit;
	return (total);
}

int		ants_treat(t_data *env, int id)
{
	int					i;
	int					limit;
	int					total_cost;
	int					tmp;

	i = 0;
	limit = 1;
	env->total_road = 0;
	total_cost = treat_better(env, limit, id);
	while (limit < env->road_sol[id + 1][0])
	{
		limit++;
		tmp = total_cost;
		total_cost = treat_better(env, limit, id);
		if (total_cost >= tmp)
		{
			i++;
			total_cost = tmp;
		}
	}
	limit -= i;
	env->road_sol[id + 1][0] = limit;
	env->road_sol[id + 1][1] = total_cost;
	return (1);
}
