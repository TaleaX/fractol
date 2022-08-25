/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bship.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:48:09 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/25 16:12:54 by tdehne           ###   ########.fr       */
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

void	calc_bship(t_pxl_data *pxl, t_all_s *all_s)
{
	double	re;
	double	im;
	int		counter;

	counter = 0;
	all_s->fractal->c_r = pxl->wx * -1;
	all_s->fractal->c_i = pxl->wy * -1;
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
		all_s->fractal->z_r = fabs(re);
		all_s->fractal->z_i = fabs(im);
		counter++;
	}
}

void	make_bship(t_pxl_data *pxl, t_all_s *all_s)
{
	all_s->g_vars->s_x = 0;
	while (all_s->g_vars->s_x < all_s->vars->win_width)
	{
		all_s->g_vars->s_y = 0;
		while (all_s->g_vars->s_y < all_s->vars->win_height)
		{
			screen_to_world(all_s->g_vars);
			pxl->wx = all_s->g_vars->w_x;
			pxl->wy = all_s->g_vars->w_y;
			pxl->px = all_s->g_vars->s_x;
			pxl->py = all_s->g_vars->s_y;
			all_s->fractal->z_r = 0.0;
			all_s->fractal->z_i = 0.0;
			calc_bship(pxl, all_s);
			pxl++;
			all_s->g_vars->s_y++;
		}
		all_s->g_vars->s_x++;
	}
	pxl->px = -1;
}
