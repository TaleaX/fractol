/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:29:07 by tdehne            #+#    #+#             */
/*   Updated: 2022/04/05 12:19:51 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	is_in_set(char const *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static long long	get_len(char const *s1, char const *set, long long start)
{
	long long	end;

	end = ft_strlen(s1) - 1;
	while (end >= 0 && is_in_set(set, s1[end]))
		end--;
	if (end < 0 || (size_t) start == ft_strlen(s1))
		return (0);
	return ((end + 1) - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str_trim;
	long long	len;
	long long	i;
	long long	start;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (is_in_set(set, s1[start]))
		start++;
	len = get_len(s1, set, start);
	str_trim = (char *) malloc(sizeof(char) * len + 1);
	if (!str_trim)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str_trim[i] = s1[start + i];
		i++;
	}
	str_trim[i] = '\0';
	return (str_trim);
}
