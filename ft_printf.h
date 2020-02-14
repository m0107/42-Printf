/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 20:14:04 by mgupta            #+#    #+#             */
/*   Updated: 2020/01/30 20:14:06 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdio.h> 
# include <stdarg.h>

typedef struct		t_block
{
	unsigned int	o_flag;
	unsigned int	dash_flag;
	int				min_width;
	unsigned int	prec_flag;
	int				prec_length;
	char			specifier;
	int				length;
}					s_block;

char	*convert(long long num, int base, s_block block);
int		ft_printf(char* format,...);
int		c_parser(s_block block, va_list arg);
int		d_parser(s_block block, va_list arg);
int		p_parser(s_block block, va_list arg);
int		per_parser(s_block block);
int		s_parser(s_block block, va_list arg);
int		s_parser_1(char *s, s_block block, int i);
int		u_parser(s_block block, va_list arg);
int		x_parser(s_block block, va_list arg);
int		X_parser(s_block block, va_list arg);

void	printspacehelper(s_block block);
#endif