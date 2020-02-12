/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:50:51 by flhember          #+#    #+#             */
/*   Updated: 2019/05/02 15:01:58 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_get_bin(void *oct, int size)
{
	int		i;
	int		j;
	char	*str;
	char	*ptr;

	if (!(str = ft_memalloc(sizeof(char) * (size * 8) + 1)))
		return (NULL);
	ptr = (char*)oct;
	i = 8;
	j = size;
	while (j--)
	{
		i = 8;
		while (i--)
			str[(j * 8) + 8 - (i + 1)] = (*ptr >> i & 1) + '0';
		ptr++;
	}
	str[size * 8] = '\0';
	return (str);
}

char		*ft_convert_b(va_list ap, char *str)
{
	double		f;
	char		*str_final;

	f = 0;
	str_final = NULL;
	ft_strdel(&str);
	f = va_arg(ap, double);
	str_final = ft_get_bin(&f, sizeof(f));
	return (str_final);
}
