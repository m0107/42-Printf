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
    printf("\nBlock info END\n");
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



void ft_printf(char* format,...) 
{ 
    printf("Input : \t%s\n",format);
   
    s_block  block;
    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format);
    while(*format != '\0')
    {
        while(*format != '%'&& *format != '\0')
        {
            putchar(*format);
            format++;
        }
        if(*format == '\0')
            return;
        block = createBlock(&format);
        printBlock(block); 
        //handle block
    }   
    
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

