/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:08:33 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/12 19:42:19 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	c_parser(t_block block, va_list arg)
{
	int c;
	int i;

	i = 0;
	c = va_arg(arg, int);
	if (block.dash_flag)
	{
		ft_putchar_fd(c, ++i);
		while (i++ < block.min_width)
			ft_putchar_fd(' ', 1);
		i--;
	}
	else
	{
		while (++i < block.min_width)
			ft_putchar_fd(' ', 1);
		ft_putchar_fd(c, 1);
	}
	return (i);
}
