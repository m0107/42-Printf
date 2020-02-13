/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:09:07 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/12 22:18:38 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

char	*create_null_str(void)
{
	char *s;

	s = (char *)malloc(7 * sizeof(char));
	s[0] = '(';
	s[1] = 'n';
	s[2] = 'u';
	s[3] = 'l';
	s[4] = 'l';
	s[5] = ')';
	s[6] = '\0';
	return (s);
}

void	printspacehelper(s_block block)
{
	if (block.o_flag)
		ft_putchar_fd('0', 1);
	else
		ft_putchar_fd(' ', 1);
}

char	*check_max_width(s_block block, va_list arg)
{
	int		i;
	char	*new_str;
	char	*s;

	i = 0;
	s = va_arg(arg, char *);
	if (s == NULL)
		new_str = create_null_str();
	else
		new_str = ft_strdup(s);
	if (block.prec_flag)
	{
		if (block.prec_length <= 0)
			new_str[0] = '\0';
		else if (block.prec_length < ft_strlen(new_str))
		{
			while (i < block.prec_length)
				i++;
			new_str[i] = '\0';
		}
	}
	return (new_str);
}

int		s_parser_1(char *s, s_block block, int i)
{
	//printf("\nDEBUG:s_parser_1: s = :%s\n",s);
	//	printf("\nDEBUG:s_parser_1: block.min_width   = :%d\n",block.min_width);
	//printf("\nDEBUG:s_parser_1: s.length   = :%zu\n", ft_strlen(s));
	while (i++ < (block.min_width - ft_strlen(s)) && block.min_width > 0)
	{
		printspacehelper(block);

	//	printf("\nDEBUG:s_parser_1: i in loop   = :%d\n", i);
	}
	ft_putstr_fd(s, 1);
	i = i + ft_strlen(s) - 1;
	return (i);
}

int		s_parser(s_block block, va_list arg)
{
	char	*s;
	int		i;

	i = 0;
	s = check_max_width(block, arg);
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
	free(s);
	return (i);
}
