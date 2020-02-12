/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 14:05:18 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/11 15:16:26 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list		*ft_lstcheck(t_list **save, int fd)
{
	t_list *tmp;

	tmp = *save;
	if (fd < 0)
		return (NULL);
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(save, tmp);
	return (tmp);
}

char		*ft_save(char *save, char **line)
{
	int		i;
	char	*tmp;

	if (!(tmp = ft_strdup(save)))
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i])
		i++;
	if (!(*line = ft_strsub(tmp, 0, i)))
		return (NULL);
	line++;
	ft_strdel(&save);
	if (tmp[i] == '\n')
	{
		if (!(save = ft_strdup(&tmp[i + 1])))
			return (NULL);
	}
	else
		save = "\0";
	ft_strdel(&tmp);
	return (save);
}

int			get_next_line(const int fd, char **line)
{
	static	t_list	*save;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	t_list			*current;

	current = ft_lstcheck(&save, fd);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0 && BUFF_SIZE > 0 && fd >= 0
			&& line != NULL)
	{
		buf[ret] = '\0';
		current->content = ft_strjoinfree(current->content, buf, 1);
		if (ft_strchr(buf, '\n'))
		{
			current->content = ft_save(current->content, line);
			return (1);
		}
	}
	if (ret < 0 || BUFF_SIZE <= 0 || fd < 0 || line == NULL)
		return (-1);
	if (((char*)current->content)[0] != '\0')
	{
		current->content = ft_save(current->content, line);
		return (1);
	}
	return (0);
}
