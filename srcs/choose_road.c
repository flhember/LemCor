/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:17 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/12 13:44:57 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		check_fail_state(t_data *env, int id, int state)
{
	int		i;
	t_fail	*fail;

	i = 0;
	while (i < id)
	{
		if (env->road[i]->state == state)
		{
			fail = env->road[i]->f_road;
			while (fail)
			{
				if (fail->id == id)
					return (0);
				fail = fail->next;
			}
		}
		i++;
	}
	return (1);
}

int		check_road_sol(int id, t_data *env)
{
	int i;

	i = 0;
	while (i < env->road_sol[1][0])
	{
		if (env->road_sol[0][i] == id)
			return (-1);
		i++;
	}
	return (1);
}

int		reset_state(t_data *env)
{
	int i;
	int j;
	int state;

	i = 0;
	j = 0;
	state = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 1)
		{
			if ((check_road_sol(i, env) == -1) && env->road[i]->col != 0)
			{
				j++;
				env->road[i]->state = -2;
			}
		}
		else if (env->road[i]->state == 1 || env->road[i]->state == -1)
			state++;
		i++;
	}
	return (state);
}

int		new_tab(t_data *env, int fl)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 1)
		{
			if (fl == 1)
				env->road_sol[2][j] = i;
			j++;
		}
		else if (env->road[i]->state == -1)
		{
			if (check_fail_state(env, i, env->road[i]->state) == 1)
			{
				if (fl == 1)
					env->road_sol[2][j] = i;
				j++;
			}
		}
		i++;
	}
	return (j);
}

int		choose_road(t_data *env)
{
	int ok;
	int size_tab;

	size_tab = 0;
	ok = 0;
	env->size_free = env->nb_road_f;
	size_tab = env->nb_road_f;
	if ((env->nb_road_f = choose_road_use(env)) == -1)
		return (-1);
	ants_treat(env, 0);
	env->nb_road_f = size_tab;
	if ((size_tab = reset_state(env)) == 0)
	{
		env->road_sol[3][1] = env->road_sol[1][1] + 1;
		return (1);
	}
	env->road_sol[3][0] = new_tab(env, 0);
	if (!(env->road_sol[2] =
				(int*)ft_memalloc(sizeof(int) * env->road_sol[3][0])))
		return (-1);
	new_tab(env, 1);
	env->nb_road_f = size_tab;
	ants_treat(env, 2);
	return (1);
}
