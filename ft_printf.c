/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:29:56 by mgupta            #+#    #+#             */
/*   Updated: 2020/01/30 19:29:58 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

void	init_block(t_block *block)
{
	block->dash_flag = 0;
	block->o_flag = 0;
	block->min_width = 0;
	block->prec_flag = 0;
	block->prec_length = 0;
}

t_block	create_block(char **format, va_list *arg)
{
	t_block block;

	init_block(&block);
	(*format)++;
	if (is_flag(format))
		set_flag(&block, format);
	if (is_width(**format))
		block.min_width = set_width(format);
	if (**format == '*')
	{
		block.min_width = va_arg(*arg, int);
		(*format)++;
	}
	chk_set_prec(&block, format, arg);
	block.specifier = **format;
	(*format)++;
	return (block);
}

void	rectify_neg_star(t_block *block)
{
	if (block->min_width < 0)
	{
		block->dash_flag = 1;
		block->min_width = (-1) * block->min_width;
	}
}

int		parse_block(t_block block, va_list *arg)
{
	rectify_neg_star(&block);
	if (block.specifier == 'c')
		return (c_parser(block, *arg));
	else if (block.specifier == 's')
		return (s_parser(block, *arg));
	else if (block.specifier == 'p')
		return (p_parser(block, *arg));
	else if (block.specifier == 'd' || block.specifier == 'i')
		return (d_parser(block, *arg));
	else if (block.specifier == 'u')
		return (u_parser(block, *arg));
	else if (block.specifier == 'x')
		return (x_parser(block, *arg));
	else if (block.specifier == 'X')
		return (xx_parser(block, *arg));
	else if (block.specifier == '%')
		return (per_parser(block));
	else
		return (0);
}

int		ft_printf(char *format, ...)
{
	t_block	block;
	va_list	arg;
	int		length;

	length = 0;
	va_start(arg, format);
	while (*format != '\0')
	{
		while (*format != '%' && *format != '\0')
		{
			ft_putchar_fd(*format, 1);
			format++;
			length++;
		}
		if (*format == '\0')
			break ;
		block = create_block(&format, &arg);
		length = length + parse_block(block, &arg);
	}
	va_end(arg);
	return (length);
}
