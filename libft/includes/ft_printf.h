/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:35:34 by bmouhib           #+#    #+#             */
/*   Updated: 2024/06/12 17:12:08 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <string.h>
/*
All optional flags for the function ft_printf :
- left		: '-', the result is left-justified
- sign		: '+', the sign is shown for integers, float. numbers
- space		: ' ', if
- hash		: '#', alternate conversion for integers
- zero		: '0', space padding replaced by zeros, ignored if precision specified
- precision	: '.[int/star]' 
*/
typedef struct s_flag
{
	int	left;
	int	sign;
	int	space;
	int	hash;
	int	zero;
	int	star;
	int	width;
	int	precision;
	int	type;
}	t_flag;

t_flag	init_flag(void);
int		is_type(char c);
int		ft_pad_math(t_flag flag, char *num, long long nb);
int		ft_size(unsigned long int nb, long long int base);
void	ft_putnbr_caps(unsigned long nb, char *tab, int i, unsigned long base);
void	ft_putnbr(unsigned long nb, char *tab, int i, unsigned long base);
void	ft_print_var(va_list args, t_flag flag, int *count);
int		ft_printf(const char *format, ...);
void	ft_print_c(char c, int *count);
void	ft_print_char(char c, t_flag flag, int *count);
void	ft_print_s(char *c, int *count);
void	ft_print_string(char *c, t_flag flag, int *count);
void	ft_print_u(unsigned int nb, t_flag flag, int *count);
void	ft_print_x(unsigned int a, int add, t_flag flag, int *count);
int		ft_print_p(void *a, t_flag flag, int *count);
void	ft_print_padding(int len, char c, int *count);
void	ft_print_sign(t_flag flag, long long int nb, int *count);
void	ft_print_nb(long long int nb, t_flag flag, int *count);
void	flag_left(t_flag *flag);
char	*ft_itoa_printf(int n);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned long int n, int x);
char	*flag_digit(char *str, int *fdigit, t_flag *flag, va_list args);

#endif
