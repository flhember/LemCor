/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 12:03:46 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 13:47:35 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

t_room		*creat_cpy(t_lst **lst, int sec_pe)
{
	t_room	*cpy;

	cpy = NULL;
	if (!(cpy = ft_memalloc(sizeof(t_room))))
		return (NULL);
	cpy->name = ft_strdup((*lst)->tab[sec_pe]->name);
	cpy->pos = (*lst)->tab[sec_pe]->pos;
	cpy->x = (*lst)->tab[sec_pe]->x;
	cpy->y = (*lst)->tab[sec_pe]->y;
	cpy->start = (*lst)->tab[sec_pe]->start;
	cpy->end = (*lst)->tab[sec_pe]->end;
	cpy->next = NULL;
	return (cpy);
}

int			add_link_lst(t_lst **lst, int fst_pe, int sec_pe)
{
	t_room	*cpy;
	t_room	*lst_cpy;

	lst_cpy = (*lst)->tab[fst_pe];
	if (!(cpy = creat_cpy(lst, sec_pe)))
		return (-1);
	while (lst_cpy->next)
		lst_cpy = lst_cpy->next;
	lst_cpy->next = cpy;
	return (0);
}

int			find_good_room(t_data *env, t_lst **lst, t_stock **pipe, size_t k)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_is_c((*pipe)->room, '-') == 1)
		(*pipe)->room1 =
			ft_strncut((*pipe)->room, ft_strnlen((*pipe)->room, '-'));
	else
		(*pipe)->room1 = ft_strdup((*pipe)->room);
	while (i < env->nb_room && ft_strcmp((*lst)->tab[i]->name,
				(*pipe)->room1) != 0)
		i++;
	if (i == env->nb_room)
		return (-1);
	j = ft_strlen((*lst)->tab[i]->name);
	if (j < ft_strlen((*pipe)->room))
	{
		while (k < (j + 1))
		{
			(*pipe)->room++;
			k++;
		}
	}
	ft_strdel(&(*pipe)->room1);
	return ((*lst)->tab[i]->pos);
}

int			find_stock_pipe(t_data *env, t_lst **lst, t_stock *pipe)
{
	int		fst_pe;
	int		sec_pe;
	char	*str;

	str = pipe->room;
	if ((fst_pe = find_good_room(env, lst, &pipe, 0)) == -1)
	{
		ft_strdel(&pipe->room1);
		ft_strdel(&str);
		return (-1);
	}
	if ((sec_pe = find_good_room(env, lst, &pipe, 0)) == -1)
	{
		ft_strdel(&pipe->room1);
		ft_strdel(&str);
		return (-1);
	}
	pipe->room = str;
	if (add_link_lst(lst, fst_pe, sec_pe) == -1)
		return (-1);
	if (add_link_lst(lst, sec_pe, fst_pe) == -1)
		return (-1);
	return (0);
}

int			stock_pipe(t_data *env, t_lst **lst, t_stock *pipe)
{
	while (pipe)
	{
		if (pipe->pipe == 1)
		{
			if ((find_stock_pipe(env, lst, pipe)) == -1)
			{
				pipe->room = NULL;
				return (-1);
			}
		}
		pipe = pipe->next;
	}
	return (0);
}
