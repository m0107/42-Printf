/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xX_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:09:21 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/11 21:09:22 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	x_parser(s_block block, va_list arg)
{
	int i;
	
	i = va_arg(arg,int);
	ft_putchar_fd(i,1);
}

int	X_parser(s_block block, va_list arg)
{
	int i;
	
	i = va_arg(arg,int);
	ft_putchar_fd(i,1);
}