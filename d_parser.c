/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:08:41 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/16 00:39:10 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*convert_str2no_1(t_block block, char *new_str, char *temp)
{
	char	*s;
	int		i;

	i = -1;
	s = (char *)malloc(block.prec_length + 3);
	if (*new_str == '-')
	{
		s[++i] = '-';
		new_str++;
		block.prec_length++;
	}
	while (++i < block.prec_length - ft_strlen(new_str))
		s[i] = '0';
	while (i < block.prec_length)
		s[i++] = *new_str++;
	s[i] = '\0';
	free(temp);
	return (s);
}

char	*convert_str2no(t_block block, va_list arg)
{
	char	*new_str;
	int		n;
	char	*temp;

	n = va_arg(arg, int);
	new_str = ft_itoa(n);
	temp = new_str;
	if (*new_str == '0' && block.prec_flag)
		*new_str = '\0';
	if (block.prec_flag && block.prec_length >= ft_strlen(new_str))
	{
		return (convert_str2no_1(block, new_str, temp));
	}
	return (new_str);
}

void	printspacehelper_d(t_block block)
{
	if (block.o_flag && !block.prec_flag)
		ft_putchar_fd('0', 1);
	else
		ft_putchar_fd(' ', 1);
}

int		d_parser_1(char *s, t_block block, int i)
{
	if (*s == '-' && (block.dash_flag || (block.o_flag && !block.prec_flag)))
	{
		s++;
		i++;
		ft_putchar_fd('-', 1);
	}
	while (i++ < (block.min_width - ft_strlen(s)) && block.min_width > 0)
		printspacehelper_d(block);
	ft_putstr_fd(s, 1);
	i = i + ft_strlen(s) - 1;
	return (i);
}

int		d_parser(t_block block, va_list arg)
{
	char	*s;
	int		i;

	i = 0;
	s = convert_str2no(block, arg);
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
		i = d_parser_1(s, block, i);
	free(s);
	return (i);
}
