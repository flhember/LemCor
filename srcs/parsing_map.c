/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:26:44 by flhember          #+#    #+#             */
/*   Updated: 2020/02/12 14:51:05 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		check_start_end(char *str, t_data *env, t_stock **lst)
{
	if (ft_strcmp(str + 2, "start") == 0 && add_flag(env, START)
			== 0 && (env->se & AEND) == 0)
	{
		env->flags |= START;
		env->se |= ASTART;
		return (1);
	}
	else if (ft_strcmp(str + 2, "end") == 0
			&& add_flag(env, END) == 0 && (env->se & ASTART) == 0)
	{
		env->flags |= END;
		env->se |= AEND;
		return (1);
	}
	else
		return (-1);
	if (creat_maillon(lst, str, "0", "0") == -1)
		return (-1);
	(*lst)->com = 1;
	return (1);
}

int		check_room(t_stock **lst, char *str, t_data *env)
{
	if (str[0] == '#' && str[1] == '#' && (check_start_end(str, env, lst) == 1))
		return (1);
	else if (str[0] == '#' && str[1] != '#')
	{
		if (creat_maillon(lst, str, "0", "0") == -1)
			return (-1);
		(*lst)->com = 1;
		return (1);
	}
	return (1);
}

int		check_tube(char *str, t_stock **lst, t_data *env)
{
	if (ft_count_c(str, '-') == 1 && ft_count_c(str, ' ') == 0)
	{
		if (creat_maillon(lst, str, "0", "0") == -1)
			return (-1);
		(*lst)->pipe = 1;
		env->nb_con++;
		env->se |= PIPE;
		return (1);
	}
	else
		return (-1);
}

int		check_line(char *str, t_data *env, t_stock **lst)
{
	if (str[0] == '#')
	{
		if (check_room(lst, str, env) == 1)
			return (1);
	}
	else if (ft_strisdigit(str) == 1
	|| (str[0] == '-' && ft_strisdigit(str + 1) == 1))
	{
		if (check_nb_ants(str, env) == 1)
			return (1);
	}
	else if (ft_is_c(str, '-')
			&& (env->se & PSTART) != 0 && (env->se & PEND) != 0)
	{
		if (check_tube(str, lst, env) == 1)
			return (1);
	}
	else
	{
		if (check_valid_room(str, env, lst) == 1 && (env->se & PIPE) == 0)
			return (1);
	}
	return (-1);
}

int		parsing_map(t_data *env, t_stock **lst)
{
	char *line;

	(*lst)->pipe = 0;
	line = NULL;
	while ((line = ft_get_fd(0)))
	{
		if (check_line(line, env, lst) != 1)
		{
			line != NULL ? free(line) : line;
			if ((env->se & PIPE) != 0)
				break ;
			return (-1);
		}
		free(line);
	}
	if (env->nb_con > 0 && add_flag(env, START) && add_flag(env, END))
		return (1);
	else
		return (-1);
}
