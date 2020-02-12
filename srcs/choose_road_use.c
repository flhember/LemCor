/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_road_use.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:14:06 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/12 17:15:16 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		check_fail(t_data *env, int id)
{
	int		i;
	t_fail	*fail;

	i = 0;
	while (i < id)
	{
		fail = env->road[i]->f_road;
		while (fail)
		{
			if (fail->id == id)
				return (0);
			fail = fail->next;
		}
		i++;
	}
	return (1);
}

int		get_ok(t_data *env)
{
	int i;
	int safe;

	i = 0;
	safe = 0;
	while (i < env->nb_road_f)
	{
		if (check_fail(env, i) == 1)
		{
			env->road[i]->state = 1;
			safe++;
		}
		else
			env->road[i]->state = -1;
		i++;
	}
	return (safe);
}

int		choose_road_use(t_data *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(env->road_sol = (int**)ft_memalloc(sizeof(int*) * 4)))
		return (-1);
	if (!(env->road_sol[0] = (int*)ft_memalloc(sizeof(int) * get_ok(env))))
		return (-1);
	if (!(env->road_sol[1] = (int*)ft_memalloc(sizeof(int) * 2)))
		return (-1);
	env->road_sol[1][0] = get_ok(env);
	if (!(env->road_sol[3] = (int*)ft_memalloc(sizeof(int) * 2)))
		return (-1);
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 1)
		{
			env->road_sol[0][j] = i;
			j++;
		}
		i++;
	}
	return (j);
}
