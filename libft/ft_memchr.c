/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:07:17 by tdehne            #+#    #+#             */
/*   Updated: 2022/03/26 16:08:13 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*d_s;

	d_s = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (d_s[i] == (unsigned char) c)
			return (d_s + i);
		i++;
	}
	return (0);
}
