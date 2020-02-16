/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 03:48:04 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/16 03:48:09 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_flag(char **format)
{
	while (**format == ' ')
		(*format)++;
	if (**format == '0' || **format == '-')
		return (1);
	return (0);
}

void	set_flag(t_block *block, char **format)
{
	while (is_flag(format))
	{
		if (**format == '-')
			block->dash_flag = 1;
		else if (**format == '0')
			block->o_flag = 1;
		(*format)++;
	}
}

int		is_width(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		set_width(char **format)
{
	char	s[100];
	int		i;

	i = 0;
	while (is_width(**format))
	{
		s[i++] = **format;
		(*format)++;
	}
	s[i] = '\0';
	return (ft_atoi(s));
}

void	chk_set_prec(t_block *block, char **format, va_list *arg)
{
	if (**format == '.')
	{
		block->prec_flag = 1;
		(*format)++;
		if (**format == '*')
		{
			block->prec_length = va_arg(*arg, int);
			if (block->prec_length < 0)
			{
				block->prec_flag = 0;
				block->prec_length = 0;
			}
			(*format)++;
		}
		else
			block->prec_length = set_width(format);
	}
}
