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


#include "ft_printf.h"

char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}


void ft_printf(char* format,...) 
{ 
    unsigned int i; 
    char *s; 

    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format);
    while (*format != '\0') 
    { 
        while( *format != '%' && * format != '\0') 
        {   
          //  printf("\nwhile FORMAT:|%c|\n",*format);                        
            ft_putchar_fd(*format,1);
            format++; 
        } 
        if ( *format == '\0' )
          break;
        format++; 
        //Module 2: Fetching and executing arguments
        switch(*format) 
        { 
            case 'c' : i = va_arg(arg,int);     //Fetch char argument
                        ft_putchar_fd(i,1);
                        break;
            case 'u' : i = va_arg(arg,unsigned int);     //Fetch char argument
                        ft_putstr_fd(convert(i,10),1);
                        break; 

            case 'd' : i = va_arg(arg,int);         //Fetch Decimal/Integer argument
                        if(i<0) 
                        { 
                            i = -i;
                            ft_putchar_fd('-',1); 
                        } 
                        ft_putstr_fd(convert(i,10),1);
                        break; 

            case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
                        ft_putstr_fd(convert(i,8),1);
                        break; 

            case 's': s = va_arg(arg,char *);       //Fetch string
            //            printf("\nswitch\n+  FORMAT:%c\n",*format);
                        ft_putstr_fd(s,1); 
                        break; 

            case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
                        ft_putstr_fd(convert(i,16),1);
                        break; 
            default : ft_putstr_fd("HEllo",1);
        }   
        format++;
    } 

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

