/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_res.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:03:05 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:47:20 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_start(t_data *env)
{
	int		i;
	t_road	*tmp;

	i = 0;
	tmp = NULL;
	while (i < env->road_sol[env->tab_choose][0])
	{
		if (env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant > 0)
		{
			tmp = env->road[env->road_sol[env->tab_choose - 1][i]];
			tmp = tmp->next;
			ft_printf("L%d-%s", env->nb_ant_go, tmp->name);
			if (i + 1 < env->road_sol[env->tab_choose][0])
				ft_printf(" ");
			tmp->ant_now = env->nb_ant_go;
			env->nb_ant_go++;
			env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant--;
		}
		i++;
	}
}

void		print_cont_bis(t_data *env, int search, int flg, int i)
{
	t_road	*tmp;

	while (flg == 1 && i < env->road_sol[env->tab_choose][0])
	{
		tmp = env->road[env->road_sol[env->tab_choose - 1][i++]];
		while (tmp)
		{
			if (tmp->ant_now == search)
			{
				flg = 0;
				tmp->ant_now = 0;
				if (tmp->next)
				{
					tmp = tmp->next;
					tmp->ant_move = search;
					ft_printf("L%d-%s", search, tmp->name);
					if (search + env->print_st_ok < env->nb_ant_go)
						ft_printf(" ");
				}
				else
					env->ant_finish++;
			}
			tmp = tmp->next;
		}
	}
}

void		print_cont(t_data *env)
{
	int		start;

	start = 1;
	while (start < env->nb_ant_go)
	{
		print_cont_bis(env, start, 1, 0);
		start++;
	}
}

void		reset_ant(t_data *env)
{
	int		i;
	t_road	*tmp;

	i = 0;
	while (i < env->road_sol[env->tab_choose][0])
	{
		tmp = env->road[env->road_sol[env->tab_choose - 1][i]];
		while (tmp)
		{
			if (tmp->ant_move > 0)
			{
				tmp->ant_now = tmp->ant_move;
				tmp->ant_move = 0;
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void		print_res(t_data *env, int i, int nb_line, int nb_max)
{
	ft_putchar('\n');
	nb_max = find_nb_max(env);
	while (i < nb_max)
	{
		if (i > 0)
			print_cont(env);
		print_start(env);
		reset_ant(env);
		ft_printf("\n");
		i++;
		nb_line++;
	}
	env->print_st_ok = 1;
	while (env->ant_finish < env->nb_ant_go - 1)
	{
		print_cont(env);
		reset_ant(env);
		if (env->ant_finish < env->nb_ant_go - 1)
		{
			ft_printf("\n");
			nb_line++;
		}
	}
	env->line == 1 ? ft_printf("\n\n[%d] lines\n", nb_line) : env->line;
}
