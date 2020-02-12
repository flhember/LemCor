/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:02:54 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:48:03 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			find_nb_max(t_data *env)
{
	int		i;
	int		nb_max;

	i = 0;
	nb_max = 0;
	while (i < env->road_sol[env->tab_choose][0])
	{
		if (env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant > nb_max)
			nb_max = env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant;
		i++;
	}
	return (nb_max);
}

void		clean_status(t_lst **lst)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == 0)
			(*lst)->tab[i]->status = 0;
		i++;
	}
}

void		del_first_file(t_file **file)
{
	t_file	*tmp;

	tmp = *file;
	*file = (*file)->next;
	free(tmp);
}

void		check_valid_room_bis(t_data *env, t_stock **lst)
{
	if ((env->se & ASTART) != 0)
	{
		(*lst)->start = 1;
		env->se |= PSTART;
		env->se ^= ASTART;
	}
	if ((env->se & AEND) != 0)
	{
		(*lst)->end = 1;
		env->se |= PEND;
		env->se ^= AEND;
	}
}

int			check_maillon_bis(char **tab)
{
	if (tab[2][0] == '-' || ft_strisdigit(tab[2]) == 1)
	{
		if (tab[2][0] == '-')
		{
			if (ft_atoi(tab[2] + 1) < -2147483647
					|| ft_strisdigit(tab[2] + 1) != 1)
				return (-1);
		}
		else if ((ft_strisdigit(tab[2]) != 1)
				|| (ft_atoi(tab[2]) > 2147483647))
			return (-1);
		return (0);
	}
	else
		return (-1);
	return (0);
}
