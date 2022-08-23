/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:53:50 by tdehne            #+#    #+#             */
/*   Updated: 2022/04/04 17:19:58 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			counter++;
		while (*s && *s != c)
			s++;
	}
	return (counter);
}

static size_t	get_sublen(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s && *s != c)
	{
		counter++;
		s++;
	}
	return (counter);
}

static const char	*set_ptr(const char *s, char c, int to_c)
{
	if (to_c)
		while (*s && *s != c)
			s++;
	else
		while (*s && *s == c)
			s++;
	return (s);
}

static void	*free_all(char **arr, size_t i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr[i]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	len;
	size_t	sub_len;
	size_t	i;

	if (!s)
		return (NULL);
	len = get_len(s, c);
	arr = (char **) ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s = set_ptr(s, c, 0);
		if (!*s)
			break ;
		sub_len = get_sublen(s, c);
		arr[i] = ft_substr(s, 0, sub_len);
		s = set_ptr(s, c, 1);
		if (!arr[i])
			return (free_all(arr, i - 1));
		i++;
	}
	return (arr);
}
