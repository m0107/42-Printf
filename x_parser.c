/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 01:54:48 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/16 01:55:05 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*handle_prec(t_block block, char *new_str)
{
	char	*s;
	int		i;
	char	*temp;
	char	*temp1;

	i = -1;
	temp = ft_strdup(new_str);
	temp1 = temp;
	if (*temp == '0' && block.prec_flag)
		*temp = '\0';
	if (block.prec_flag && block.prec_length > ft_strlen(temp))
	{
		s = (char *)malloc(block.prec_length + 2);
		while (++i < block.prec_length - ft_strlen(temp))
			s[i] = '0';
		while (i < block.prec_length)
			s[i++] = *temp++;
		s[i] = '\0';
		free(temp1);
		return (s);
	}
	return (temp1);
}

int		x_parser_1(char *s, t_block block, int i)
{
	while (i++ < (block.min_width - ft_strlen(s)) && block.min_width > 0)
	{
		if (block.o_flag && !block.prec_flag)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
	}
	ft_putstr_fd(s, 1);
	i = i + ft_strlen(s) - 1;
	return (i);
}

char	*convert_x(long long num, int base, t_block block)
{
	static char	*representation;
	static char	buffer[50];
	char		*ptr;

	if (block.specifier == 'x')
		representation = ft_strdup("0123456789abcdef");
	else
		representation = ft_strdup("0123456789ABCDEF");
	ptr = &buffer[49];
	*ptr = '\0';
	while (1)
	{
		*--ptr = representation[num % base];
		num /= base;
		if (num == 0)
			break ;
	}
	free(representation);
	return (handle_prec(block, ptr));
}

int		x_parser(t_block block, va_list arg)
{
	int				i;
	unsigned int	l;
	char			*s;

	i = 0;
	l = va_arg(arg, unsigned int);
	s = convert_x(l, 16, block);
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
		i = x_parser_1(s, block, i);
	free(s);
	return (i);
}

int		xx_parser(t_block block, va_list arg)
{
	int				i;
	unsigned int	l;
	char			*s;

	i = 0;
	l = va_arg(arg, unsigned int);
	s = convert_x(l, 16, block);
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
		i = x_parser_1(s, block, i);
	free(s);
	return (i);
}
