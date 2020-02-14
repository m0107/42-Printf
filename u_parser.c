/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:09:14 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/11 21:09:16 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"


char	*convert_str2no_u(s_block block, va_list arg)
{
	char 	*s;
	char	*new_str;
	int		n;
	int 	i;
	char	*temp;

	i = -1;
	n = va_arg(arg, int);
	new_str = ft_itoa(n);
	temp  = new_str;
	if(*new_str == '0' && block.prec_flag)
		*new_str = '\0';
	if (block.prec_flag && block.prec_length > ft_strlen(new_str))
	{
		s = (char *)malloc(block.prec_length + 2);
		if(*new_str == '-')
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
	return (new_str);
}
void	printspacehelper_u(s_block block)
{
	if (block.o_flag && !block.prec_flag)
		ft_putchar_fd('0', 1);
	else
		ft_putchar_fd(' ', 1);
}

int		u_parser_1(char *s, s_block block, int i)
{
	//printf("\nDEBUG:s_parser_1: s = :%s\n",s);
	//	printf("\nDEBUG:s_parser_1: block.min_width   = :%d\n",block.min_width);
	//printf("\nDEBUG:s_parser_1: s.length   = :%zu\n", ft_strlen(s));
	if (*s == '-' && (block.dash_flag || (block.o_flag && !block.prec_flag)))
	{
		s++;
		i++;
		ft_putchar_fd('-',1);
	}
	while (i++ < (block.min_width - ft_strlen(s)) && block.min_width > 0)
	{
		printspacehelper_u(block);

	//	printf("\nDEBUG:s_parser_1: i in loop   = :%d\n", i);
	}
	ft_putstr_fd(s, 1);
	i = i + ft_strlen(s) - 1;
	return (i);
}


int		u_parser(s_block block, va_list arg)
{
	char	*s;
	int		i;

	i = 0;
	s = convert_str2no_u(block, arg);
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
		i = u_parser_1(s, block, i);
	free(s);
	return (i);
}