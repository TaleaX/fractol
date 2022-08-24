/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:30:08 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/24 17:20:37 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	color(int n, int max_value, double width, double offset, int reverse)
{
	double	a;
	int		r;
	int		g;
	int		b;
	int		color;

	a = reverse ? (width * (max_value - n) / max_value + M_PI / 2 + offset) : (width * n / max_value + M_PI / 2 + offset);
	r = sin(a) * 192 + 128;
	r = (r < 0) ? 0 : ((r > 255) ? 255 : r);
	g = sin(a - (2 * M_PI) / 3) * 192 + 128;
	g = (g < 0) ? 0 : ((g > 255) ? 255 : g);
	b = sin(a - (4 * M_PI) / 3) * 192 + 128;
	b = (b < 0) ? 0 : ((b > 255) ? 255 : b);
	color = get_rgba(r, g, b, 255);
	//(((((0x00 << 8) | r) << 8) | g) << 8) | b;
	return (color);
}
