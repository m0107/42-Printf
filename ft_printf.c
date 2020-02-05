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

void ft_printf(char* format,...) 
{ 
    //Module 1: Initializing Myprintf's arguments 
    va_list arg; 
    va_start(arg, format);
    parseBlock(&format)
    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 

