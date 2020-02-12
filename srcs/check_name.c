/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:52:49 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/12 13:44:49 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	print_room(size_t i, size_t j, t_lst **lst)
{
	if (i == j)
		return (1);
	if (ft_strcmp((*lst)->tab[i]->name, (*lst)->tab[j]->name) == 0)
		return (-1);
	return (1);
}

static int	check_tab(int *tab, t_data *env, t_lst **lst)
{
	size_t	i;
	size_t	j;
	int		tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (i < env->nb_room)
	{
		while (j < env->nb_room)
		{
			tmp = tab[i];
			if (tmp == tab[j])
			{
				if (print_room(i, j, lst) == -1)
					return (-1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static void	hash(char *str, int *tab, size_t i)
{
	int		hash;
	int		c;

	hash = 0;
	c = 0;
	while ((c = *str++))
		hash = c + (hash << 1);
	tab[i] = hash;
}

int			check_name(t_data *env, t_lst **lst)
{
	int		*tab;
	size_t	i;

	i = 0;
	if (!(tab = ft_memalloc(sizeof(int) * (env->nb_room))))
		return (-1);
	while (i < env->nb_room)
	{
		hash((*lst)->tab[i]->name, tab, i);
		i++;
	}
	if (check_tab(tab, env, lst) == -1)
	{
		free(tab);
		return (-1);
	}
	free(tab);
	return (1);
}
