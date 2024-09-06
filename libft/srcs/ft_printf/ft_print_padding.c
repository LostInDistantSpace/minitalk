/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_padding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmouhib <bmouhib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:32:17 by bmouhib           #+#    #+#             */
/*   Updated: 2024/06/09 22:54:21 by bmouhib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_padding(int len, char fill, int *count)
{
	while (len-- > 0)
		ft_print_c(fill, count);
}

void	ft_print_sign(t_flag flag, long long int nb, int *count)
{
	if (nb < 0)
		ft_print_c('-', count);
	else if (flag.sign)
		ft_print_c('+', count);
	else if (flag.space)
		ft_print_c(' ', count);
}
