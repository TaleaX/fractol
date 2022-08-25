/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:32:08 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/25 16:07:55 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	get_re(t_all_s *all_s)
{
	return (all_s->fractal->z_r * all_s->fractal->z_r - all_s->fractal->z_i \
			* all_s->fractal->z_i + all_s->fractal->c_r);
}

static double	get_im(t_all_s *all_s)
{
	return (2 * all_s->fractal->z_r * all_s->fractal->z_i \
			+ all_s->fractal->c_i);
}

static void	calc_julia(t_pxl_data *pxl, t_all_s *all_s)
{
	double	re;
	double	im;
	int		counter;

	counter = 0;
	while (1)
	{
		re = get_re(all_s);
		im = get_im(all_s);
		if (counter == all_s->vars->iter_depth)
		{
			pxl->counter = counter;
			break ;
		}
		if (re * re + im * im > 4.0)
		{
			pxl->counter = counter;
			break ;
		}
		all_s->fractal->z_r = re;
		all_s->fractal->z_i = im;
		counter++;
	}
}

void	make_julia(t_pxl_data *pxl, t_all_s *all_s)
{
	all_s->g_vars->s_x = 0;
	while (all_s->g_vars->s_x < all_s->vars->win_width)
	{
		all_s->g_vars->s_y = 0;
		while (all_s->g_vars->s_y < all_s->vars->win_height)
		{
			screen_to_world(all_s->g_vars);
			all_s->fractal->z_i = all_s->g_vars->w_y;
			all_s->fractal->z_r = all_s->g_vars->w_x;
			pxl->px = all_s->g_vars->s_x;
			pxl->py = all_s->g_vars->s_y;
			calc_julia(pxl, all_s);
			pxl++;
			all_s->g_vars->s_y++;
		}
		all_s->g_vars->s_x++;
	}
	pxl->px = -1;
}
