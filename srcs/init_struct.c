/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:24:12 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:49:46 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		verif_if_one_pipe(t_lst **lst, t_data *env)
{
	int		i;
	int		j;
	t_room	*tmp;

	i = 0;
	j = 0;
	tmp = (*lst)->tab[env->end];
	while (tmp)
	{
		if (tmp->pos != env->end)
			i++;
		if (tmp->pos == env->start)
			j++;
		tmp = tmp->next;
	}
	if (j == 1)
		env->nb_con = 1;
}

void		init_struct(t_data *env, int ac, char **av)
{
	env->flags = 0;
	env->se = 0;
	env->nb_ants = 0;
	env->nb_room = 0;
	env->nb_con = 0;
	env->print_st_ok = 0;
	if (ac == 2 && ft_strcmp(av[1], "-l") == 0)
		env->line = 1;
	else
		env->line = 0;
	env->nb_ant_go = 1;
	env->ant_finish = 0;
}
