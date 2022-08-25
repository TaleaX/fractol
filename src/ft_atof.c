/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:37:28 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/25 18:06:39 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static int	get_len(char *nptr)
{
	int	counter;

	counter = 0;
	while (nptr[counter])
	{
		if (nptr[counter] < '0' || nptr[counter] > '9')
			break ;
		counter++;
	}
	return (counter);
}

void	move_to_dot(char **str)
{
	while (**str && **str != '.')
		(*str)++;
}

double	ft_atof(char *str)
{
	long long	before_dot;
	double		res;
	int			len;
	int			exp;
	int			minus;

	minus = 1;
	if (ft_strchr(str, '-'))
		minus = -1;
	res = atoi(str);
	if (res == GT_MAX_INT)
		return (ERROR);
	move_to_dot(&str);
	if (*str)
		str++;
	len = get_len(str);
	exp = 1;
	while (exp <= len)
	{
		res += (*str - '0') * ft_neg_pow(10, exp);
		exp++;
	}
	return (res * minus);
}
