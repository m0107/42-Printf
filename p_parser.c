/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:08:52 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/16 01:34:31 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*convert(long long num, int base, t_block block)
{
	static char	*representation;
	static char	buffer[50];
	char		*ptr;

	representation = ft_strdup("0123456789abcdef");
	ptr = &buffer[49];
	*ptr = '\0';
	while (1)
	{
		*--ptr = representation[num % base];
		num /= base;
		if (num == 0)
			break ;
	}
	*--ptr = 'x';
	*--ptr = '0';
	if (ft_strlen(ptr) < 4 && block.prec_flag)
		ptr[2] = '\0';
	free(representation);
	return (ptr);
}

int		p_parser(t_block block, va_list arg)
{
	int			i;
	long long	l;
	char		*s;

	i = 0;
	l = va_arg(arg, unsigned long long);
	s = convert(l, 16, block);
	if (block.min_width < ft_strlen(s))
	{
		ft_putstr_fd(s, 1);
		i = ft_strlen(s);
	}
	else if (block.dash_flag)
	{
		ft_putstr_fd(s, ++i);
		i = i + ft_strlen(s) - 1;
		while (i++ < block.min_width)
			ft_putchar_fd(' ', 1);
		i--;
	}
	else
		i = s_parser_1(s, block, i);
	return (i);
}
