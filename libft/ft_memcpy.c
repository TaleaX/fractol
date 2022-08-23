/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:56:56 by tdehne            #+#    #+#             */
/*   Updated: 2022/04/04 15:43:15 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_c;
	char	*src_c;

	if (dest == src)
		return (dest);
	dest_c = (char *) dest;
	src_c = (char *) src;
	while (n--)
		*dest_c++ = *src_c++;
	return (dest);
}
