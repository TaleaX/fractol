/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_alg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:30:08 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/26 15:57:47 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	color(int n, int max_value, t_color color)
{
	double	a;
	int		r;
	int		g;
	int		b;

	a = color.width * n / max_value + M_PI / 2 + color.offset;
	if (color.reverse)
		a = color.width * (max_value - n) / max_value + M_PI / 2 + color.offset;
	r = sin(a) * 128 + 128;
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	g = sin(a - (2 * M_PI) / 3) * 192 + 128;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	b = sin(a - (4 * M_PI) / 3) * 192 + 128;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return (get_rgba(r, g, b, 255));
}
