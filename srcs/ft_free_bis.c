/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:44:00 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:46:14 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		free_blk_lst(t_blk_lst **blk)
{
	if ((*blk)->next)
		free_blk_lst(&(*blk)->next);
	free(*blk);
}

void		free_t_fail(t_fail **lst)
{
	if ((*lst)->next)
		free_t_fail(&(*lst)->next);
	free(*lst);
}

void		free_fail_road(t_data *env)
{
	int		i;

	i = 0;
	while (i < env->size_free)
	{
		if (env->road[i]->f_road)
			free_t_fail(&env->road[i]->f_road);
		i++;
	}
}

void		free_road_sol(t_data *env)
{
	int i;

	i = 0;
	while (i < 4)
	{
		free(env->road_sol[i]);
		i++;
	}
	free(env->road_sol);
}
