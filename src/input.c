/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:20:52 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/23 16:34:20 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_fractal_type(char **argv)
{
	if (!*(argv + 1))
		return (ERROR);
	else if (ft_strncmp(*(argv + 1), "mandel", 6) == 0)
		return (MANDEL);
	else if (ft_strncmp(*(argv + 1), "julia", 5) == 0)
		return (JULIA);
	return (ERROR);
}


