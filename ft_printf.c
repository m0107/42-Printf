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

void printBlock(s_block block)
{
    printf("\nBlock info START\n\n");
    printf("o_flag %d\n",block.o_flag);
    printf("dash_flag %d\n",block.dash_flag);
    printf("specifier %c\n",block.specifier);
    printf("min_width %d\n",block.min_width);
    printf("prec_flag %d\n",block.prec_flag);
    printf("prec_length %d\n",block.prec_length);
    printf("\nBlock  info END\n");
}
int isSpecifier(char c)
{
    if(c == 'c' || c == 's' || c == 'p' 
    || c == 'd' || c == 'i' || c == 'u' || c == 'x' ||c == 'X' ||c == '%')
        return (1);
    return 0;
}

int isFlag(char c)
{
    if(c == '0' || c == '-') 
        return (1);
    return 0;
}

void setFlag(s_block *block, char **format)
{   
    while(isFlag(**format)) 
    {
        //printf("\ndash_flag %d\n",block->dash_flag);
        if (**format == '-')
        {
        //    printf("getFlags : dash value set to true\n");
            block->dash_flag = 1;
        }
        else if (**format == '0')
        {
            block->o_flag = 1;
        }
        (*format)++;
    }
}

int isWidth(char c)
{
    if(c >= '0' && c <='9')
        return (1);
    return (0);
}
int  setWidth(char **format)
{
    char s[100];
    int i;

    i = 0;
    while(isWidth(**format))
    {
        s[i++] = **format;
        (*format)++;
    }
    s[i] = '\0';
//    printf("string for atoit: %s\n",s);
//    printf("int from atoit: %d\n",ft_atoi(s));
    return(ft_atoi(s));
}

void checknSetPrecision(s_block *block, char **format)
{
    if(**format == '.')
    {
        block->prec_flag = 1;
        (*format)++;
        block->prec_length = setWidth(format);
    }
}


s_block getBlock(s_block *block, char **format)
{
    //while loop to get all blocks;
    if (isFlag(**format))
    {
  //      printf("setting flag : %c\n", **format);
        setFlag(block, format);
        
    }
    if (isWidth(**format))
    {
    //    printf("setting minfield width : %c\n", **format);
        block->min_width = setWidth(format);
    }
    checknSetPrecision(block,format);
    //printf("setting specifier : %c\n", **format);
    block->specifier = **format;
    (*format)++;
    return *block;
}

void initalizeBlock(s_block *block)
{
   // printf("initalizeBlock\n");
    block->dash_flag = 0;
    block->o_flag = 0;
    block->min_width = -1;
    block->prec_flag = 0;
    block->prec_length = -1;
}

s_block createBlock(char **format)
{
    s_block block;
    initalizeBlock(&block);
    while(**format != '%')
    {
        putchar(**format);
        (*format)++;
    }
    (*format)++;
    block = getBlock(&block ,format);
    return block;
}

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


int parseBlock(s_block block, va_list arg)
{
    if(block.specifier == 'c') 
        return (c_parser(block, arg));
    else if(block.specifier == 's')
        return (s_parser(block, arg));
    else if(block.specifier == 'p')
        return (p_parser(block, arg));
    else if(block.specifier == 'd' || block.specifier == 'i')
        return (d_parser(block, arg));
    else if(block.specifier == 'u')
        return (u_parser(block, arg));
    else if(block.specifier == 'x')
        return (x_parser(block, arg));
    else if(block.specifier == 'X')
        return (X_parser(block, arg));
    else if(block.specifier == '%')
        return (per_parser(block, arg));
    else 
        printf("Error in parsing block: unkonwn specifier");
    
}

int ft_printf(char* format,...) 
{ 
    s_block  block;
    va_list arg; 
    int length;

    length = 0;
    va_start(arg, format);
    while(*format != '\0')
    {
        while(*format != '%'&& *format != '\0')
        {
            ft_putchar_fd(*format,1);
            format++;
            length++;
        }
        if(*format == '\0')
            break;
        block = createBlock(&format);
        //printBlock(block);
        length = length + parseBlock(block,arg);
    }   
    va_end(arg);
    return (length); 
} 

