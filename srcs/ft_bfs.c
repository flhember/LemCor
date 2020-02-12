/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:32:43 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:46:01 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			add_file(t_lst **lst, t_file **file, int val, int dis)
{
	t_file	*new;
	t_file	*tmp;

	new = NULL;
	tmp = *file;
	(*lst)->size_file++;
	(*lst)->tab[val]->status = 1;
	if (!(new = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	new->value = val;
	new->dist = dis;
	new->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

static int	fill_file(t_file **file, t_lst **lst, int i, t_data *env)
{
	t_room	*tmp;

	tmp = (*lst)->tab[i];
	if ((*lst)->tab[i]->end == 1)
		add_file(lst, file, i, (*lst)->tab[i]->dist + 1);
	else
	{
		while (tmp)
		{
			env->blk = tmp->pos;
			if (tmp->pos != i && (*lst)->tab[tmp->pos]->road != 0
			&& (*lst)->tab[tmp->pos]->road != -2 && (*lst)->tab[i]->end == 0)
				check_cross(lst, file, i, env);
			else if (tmp->pos != i && ((*lst)->tab[tmp->pos]->status != 0
					|| (*lst)->tab[tmp->pos]->road == -2))
				;
			else if (tmp->pos != i && (add_file(lst, file, tmp->pos,
						(*lst)->tab[i]->dist + 1)) == -1)
				return (-1);
			tmp = tmp->next;
		}
	}
	return (0);
}

static int	creat_file(t_data *env, t_lst **lst, t_file **file)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = (*lst)->tab[env->start];
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->road == 0 && tmp->pos != env->start)
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
		return (-1);
	if (!(*file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	if ((fill_file(file, lst, env->start, env)) == -1)
	{
		free_file(file);
		return (-1);
	}
	del_first_file(file);
	(*lst)->tab[env->start]->dist = 0;
	(*lst)->tab[env->start]->status = 2;
	return (1);
}

int			bfs(t_data *env, t_lst **lst, t_file *tmp)
{
	t_file	*file;

	file = NULL;
	reboot_nb_road(lst);
	clean_dist(lst);
	if (creat_file(env, lst, &file) == -1)
		return (-1);
	tmp = file;
	while (tmp && (*lst)->ret_bfs == -1)
	{
		if ((*lst)->tab[tmp->value]->end == 1)
			(*lst)->ret_bfs = 0;
		(*lst)->tab[tmp->value]->dist = tmp->dist;
		if ((fill_file(&tmp, lst, tmp->value, env)) == -1)
		{
			free_file(&file);
			return (-1);
		}
		(*lst)->tab[tmp->value]->status = 2;
		tmp = tmp->next;
		(*lst)->size_file--;
	}
	clean_status(lst);
	free_file(&file);
	return ((*lst)->ret_bfs);
}
