/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   per_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:09:00 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/13 17:36:52 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	per_parser(s_block block)
{
	int			i;
	char		*s;

	i = 0;
	s = "%";
	if (block.min_width < (int)ft_strlen(s))
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
