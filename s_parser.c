/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgupta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 21:09:07 by mgupta            #+#    #+#             */
/*   Updated: 2020/02/11 21:09:09 by mgupta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"


void	checkMaxWidth(char **s, s_block block)
{
	int i;
	printf("checkMaxWidth : %d\n", block.prec_length);
	i = 0;
	if(block.prec_flag)
	{
		if(block.prec_length <= 0)
			*s = "";
		else if (block.prec_length < ft_strlen(*s))
		{
			while (i < block.prec_length)
				i++;
			printf("value of i : %d\n",i);
			printf("value of s at i : %c\n", (*s)[i]);
			(*s)[i]='\0';
		}	
	}
//	printf("hecking bus error\n");
//	printf("%s\n",*s);
}
void	s_parser(s_block block, va_list arg)
{
	char  *s;
	int i;

	i = 0;
	s = va_arg(arg,char *);
	checkMaxWidth(&s,block);
	if (block.min_width < ft_strlen(s))
		ft_putstr_fd(s,1);
	else if (block.dash_flag)
	{
		ft_putstr_fd(s,++i);
		i = i + ft_strlen(s) - 1;
		while (i++ < block.min_width)
			ft_putchar_fd(' ',1);
	}
	else
	{
		while (i++ < (block.min_width - ft_strlen(s)))
			ft_putchar_fd(' ',1);		
		ft_putstr_fd(s,1);
	}
}