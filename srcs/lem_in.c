/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 16:28:51 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void	start_to_end(t_data *env, t_lst **lst)
{
	int	i;

	i = 1;
	ft_putchar('\n');
	while (i <= (int)env->nb_ants)
	{
		ft_printf("L%d-%s", i, (*lst)->tab[env->end]->name);
		if (i + 1 <= (int)env->nb_ants)
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	free_road_adja(env, (*lst)->malloc_start);
	free_lst_adja(lst, env);
	if (env->line == 1)
		ft_printf("\n\n[1] line\n");
}

void	lem_in_next(t_data *env, t_lst **lst)
{
	if (sort_road(env, 0) == -1)
	{
		free_fail_road(env);
		free_road_sol(env);
		free_road_adja(env, (*lst)->malloc_start);
		free_lst_adja(lst, env);
		return ;
	}
	env->tab_choose = env->road_sol[1][1] > env->road_sol[3][1] ? 3 : 1;
	nb_ant_road(env, 0);
	print_res(env, 0, 0, 0);
	free_fail_road(env);
	free_road_sol(env);
	free_road_adja(env, (*lst)->malloc_start);
	free_lst_adja(lst, env);
}

int		lem_in(int ac, char **av)
{
	t_data		env;
	t_lst		*lst;

	lst = NULL;
	init_struct(&env, ac, av);
	if (!(lst = parsing_main(&env)))
	{
		ft_putstr_fd("ERROR\n", 2);
		return (-1);
	}
	if ((algo_main(&lst, &env) == -1))
	{
		free_lst_adja(&lst, &env);
		return (-1);
	}
	if (lst->nb_room == 2 || env.nb_con == 1)
	{
		start_to_end(&env, &lst);
		return (0);
	}
	lem_in_next(&env, &lst);
	return (0);
}
