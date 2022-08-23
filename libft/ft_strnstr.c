/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:20:59 by tdehne            #+#    #+#             */
/*   Updated: 2022/04/02 18:20:59 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[j + i] && (i + j) < len)
			j++;
		if (j == ft_strlen(needle))
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
