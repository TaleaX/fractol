/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:45:18 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/19 15:58:17 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	lb_index(const char *str)
{
	long	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_strjoin2(char *s1, char *s2)
{
	char	*str_concat;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	str_concat = (char *) malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str_concat)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_concat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str_concat[j + i] = s2[j];
		j++;
	}
	str_concat[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (str_concat);
}

static char	*make_return(char **buf, char *tmp, int found_lb)
{
	char	*buf_tmp;

	if (!tmp)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	if (found_lb)
	{
		buf_tmp = ft_strdup((*buf) + lb_index(*buf) + 1);
		ft_memset((*buf), '\0', BUFFER_SIZE + 1);
		ft_memcpy((*buf), buf_tmp, ft_strlen(buf_tmp));
		free(buf_tmp);
		buf_tmp = ft_substr(tmp, 0, lb_index(tmp) + 1);
	}
	else
	{
		if (*buf)
			free(*buf);
		buf_tmp = ft_substr(tmp, 0, ft_strlen(tmp));
	}
	free(tmp);
	return (buf_tmp);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*tmp;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buf)
		buf = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	tmp = NULL;
	if (!buf)
		return (NULL);
	while (1)
	{
		if (*buf)
		{
			tmp = ft_strjoin2(tmp, buf);
			if (!tmp)
				break ;
			if (lb_index(tmp) >= 0)
				return (make_return(&buf, tmp, 1));
			ft_memset(buf, '\0', BUFFER_SIZE + 1);
		}
		if (read(fd, buf, BUFFER_SIZE) < 1)
			break ;
	}
	return (make_return(&buf, tmp, 0));
}
