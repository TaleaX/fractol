/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:08:25 by tdehne            #+#    #+#             */
/*   Updated: 2022/04/04 15:52:12 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_strnum_len(long n)
{
	int	counter;

	counter = 0;
	if (!n)
		return (1);
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

static long	ft_abs(long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	int			minus;
	long		num;

	minus = 0;
	if (n < 0)
		minus = 1;
	num = ft_abs((long) n);
	len = get_strnum_len(num);
	if (minus)
		len++;
	str = (char *) malloc(sizeof(char) * len + 1);
	if (!str)
		return ((void *) 0);
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = (num % 10) + '0';
		num = num / 10;
		if (minus && len == 0)
			str[len] = '-';
	}
	return (str);
}
