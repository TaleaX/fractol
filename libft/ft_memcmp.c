/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:05:56 by tdehne            #+#    #+#             */
/*   Updated: 2022/03/26 17:16:03 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*d_s1;
	unsigned char	*d_s2;

	d_s1 = (unsigned char *) s1;
	d_s2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (d_s1[i] != d_s2[i])
			return (d_s1[i] - d_s2[i]);
		i++;
	}
	return (0);
}
