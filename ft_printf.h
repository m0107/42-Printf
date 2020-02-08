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
}					s_block;

char	*convert(unsigned int num, int base);
void	ft_printf(char* format,...);

#endif