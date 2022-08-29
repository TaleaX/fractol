/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:37:28 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/29 18:24:35 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static double	ft_neg_pow(int base, int exp)
{
	double	result;

	result = 1;
	while (exp)
	{
		result /= base;
		exp--;
	}
	return (result);
}

void	move_to_dot(char **str)
{
	while (**str && **str != '.')
		(*str)++;
}

double	ft_atof(char *str)
{
	double		res;
	int			exp;
	int			minus;

	minus = 1;
	if (ft_strchr(str, '-'))
		minus = -1;
	res = ft_atoi(str);
	if (res == GT_MAX_INT)
		return (GT_MAX_INT);
	move_to_dot(&str);
	if (*str)
		str++;
	exp = 1;
	while (*str && ft_isdigit(*str))
	{
		res += (*str - '0') * ft_neg_pow(10, exp);
		exp++;
		str++;
	}
	if (*str)
		return (GT_MAX_INT);
	return (res * minus);
}
