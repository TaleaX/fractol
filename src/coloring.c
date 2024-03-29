/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:08:49 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/29 15:23:22 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_shift(t_pxl_data *pxl, t_all_s *all_s)
{
	if (all_s->color->dynamic_max)
		all_s->color->max_value = all_s->vars->iter_depth;
	all_s->color->width = all_s->vars->color_width * M_PI / 3 \
		+ sin(all_s->g_vars->count / 20.0) + 1;
	all_s->color->offset = all_s->vars->color_offset * M_PI / 3 \
		+ sin(all_s->g_vars->count / 20.0) + 1;
	all_s->color->reverse = all_s->vars->color_reverse;
	if (pxl->px < all_s->vars->win_width && pxl->px >= 0
		&& pxl->py < all_s->vars->win_height && pxl->py >= 0)
		mlx_put_pixel(all_s->img->img, pxl->px, pxl->py, \
			color(pxl->counter, all_s->color->max_value, *all_s->color));
}

void	color_normal(t_pxl_data *pxl, t_all_s *all_s)
{
	if (all_s->color->dynamic_max)
		all_s->color->max_value = all_s->vars->iter_depth;
	all_s->color->width = all_s->vars->color_width * M_PI / 3;
	all_s->color->offset = all_s->vars->color_offset * M_PI / 3;
	all_s->color->reverse = all_s->vars->color_reverse;
	if (pxl->px < all_s->vars->win_width && pxl->px >= 0
		&& pxl->py < all_s->vars->win_height && pxl->py >= 0)
		mlx_put_pixel(all_s->img->img, pxl->px, pxl->py, \
			color(pxl->counter, all_s->color->max_value, *all_s->color));
}
