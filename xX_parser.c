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

char	*handle_prec(s_block block, char *new_str)
{
	char 	*s;
	int 	i;
	char	*temp;
	char	*temp1;

	i = -1;
	temp  = ft_strdup(new_str);
	temp1 = temp;
	//printf("\nDEBUG: s = :%s\n",temp);
	//printf("\nDEBUG: s.length = :%d\n",ft_strlen(temp));
	
	if(*temp == '0' && block.prec_flag)
		*temp = '\0';
	if (block.prec_flag && block.prec_length > ft_strlen(temp))
	{
		s = (char *)malloc(block.prec_length + 2);
		while (++i < block.prec_length - ft_strlen(temp))
			s[i] = '0';
		while (i < block.prec_length)
			s[i++] = *temp++;
		s[i] = '\0';
		free(temp1);
		return (s);
	}
	return (temp1);
}


int		x_parser_1(char *s, s_block block, int i)
{
	//printf("\nDEBUG:s_parser_1: s = :%s\n",s);
	//	printf("\nDEBUG:s_parser_1: block.min_width   = :%d\n",block.min_width);
	//printf("\nDEBUG:s_parser_1: s.length   = :%zu\n", ft_strlen(s));
	while (i++ < (block.min_width - ft_strlen(s)) && block.min_width > 0)
	{
		if (block.o_flag && !block.prec_flag)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
	}
	ft_putstr_fd(s, 1);
	i = i + ft_strlen(s) - 1;
	return (i);
}

char *convert_x(long long num, int base, s_block block) 
{ 
    char Representation[]= "0123456789abcdef";
    char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 
	if(ft_strlen(ptr) < 1 && block.prec_flag){
		(void) block;
	};
    return(handle_prec(block, ptr)); 
}

char *convert_X(long long num, int base, s_block block) 
{ 
    char Representation[]= "0123456789ABCDEF";
    char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 
	if(ft_strlen(ptr) < 1 && block.prec_flag){
		(void) block;
	};
    return(handle_prec(block, ptr)); 
}


int	x_parser(s_block block, va_list arg)
{
	int			i;
	unsigned int	l;
	char *s;
	
	i = 0;
	l = va_arg(arg,unsigned int);
	//printf("\nDEBUG: l = :%u\n",l);
	s = convert_x(l,16, block);
	
	//printf("\nDEBUG: s = :%s\n",s);
	//printf("\nDEBUG: s.length = :%d\n",ft_strlen(s));
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
		i = x_parser_1(s, block, i);
	free(s);
	return (i);
}

int	X_parser(s_block block, va_list arg)
{
	int			i;
	unsigned int	l;
	char *s;
	
	i = 0;
	l = va_arg(arg, unsigned int);
	//printf("\nDEBUG: l = :%u\n",l);
	s = convert_X(l,16, block);
	
	//printf("\nDEBUG: s = :%s\n",s);
	//printf("\nDEBUG: s.length = :%d\n",ft_strlen(s));
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
		i = x_parser_1(s, block, i);
	free(s);
	return (i);
}