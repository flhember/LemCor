/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_for_best.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:05:49 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 17:26:13 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		free_file(t_file **file)
{
	if (*file != NULL)
		free_file(&(*file)->next);
	free(*file);
}

static int	add_file_best(t_lst **lst, t_file **file, int val, int dis)
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

static int	fill_file(t_file **file, t_lst **lst, int i)
{
	t_room	*tmp;

	tmp = (*lst)->tab[i];
	if ((*lst)->tab[i]->end == 1)
		add_file_best(lst, file, i, (*lst)->tab[i]->dist + 1);
	else
	{
		while (tmp)
		{
			if (tmp->pos != i)
			{
				if ((*lst)->tab[tmp->pos]->status == 0 && (add_file_best(lst, file, tmp->pos,
						(*lst)->tab[i]->dist + 1)) == -1)
					return (-1);
			}
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
	if ((fill_file(file, lst, env->start)) == -1)
	{
		free_file(file);
		return (-1);
	}
	del_first_file(file);
	(*lst)->tab[env->start]->dist = 0;
	(*lst)->tab[env->start]->status = 2;
	return (1);
}

int			bfs_best(t_data *env, t_lst **lst, t_file *tmp)
{
	t_file	*file;

	(*lst)->ret_bfs = -1;
	tmp = NULL;
	file = NULL;
	if (creat_file(env, lst, &file) == -1)
		return (-1);
	tmp = file;
	while (tmp && (*lst)->ret_bfs == -1)
	{
		if ((*lst)->tab[tmp->value]->end == 1)
			(*lst)->ret_bfs = 0;
		(*lst)->tab[tmp->value]->dist = tmp->dist;
		if ((fill_file(&tmp, lst, tmp->value)) == -1)
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
