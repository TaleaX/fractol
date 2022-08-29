/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/29 17:58:46 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"

static void	coloring(void *context)
{
	t_all_s		*all_s;
	t_pxl_data	*tmp;

	all_s = context;
	(all_s->g_vars->count)++;
	tmp = all_s->pxl;
	while (tmp->px != -1)
	{
		if (tmp->counter == all_s->vars->iter_depth)
		{
			if (tmp->px < all_s->vars->win_width && tmp->px >= 0
				&& tmp->py < all_s->vars->win_height && tmp->py >= 0)
				mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, 0x000000FF);
		}
		else if (all_s->color->shift)
			color_shift(tmp, all_s);
		else
			color_normal(tmp, all_s);
		(tmp)++;
	}
	mlx_image_to_window(all_s->vars->mlx, all_s->img->img, 0, 0);
}

void	my_keyhook(mlx_key_data_t keydata, void *context)
{
	t_all_s	*all_s;

	all_s = context;
	if (keydata.key)
		;
	if (!key_for_move(all_s) && !key_for_color(all_s)
		&& !key_core(all_s))
		return ;
	all_s->calc[all_s->fractal->frac_type](all_s->pxl, all_s);
}

void	zoom(double xdelta, double ydelta, void	*context)
{
	t_all_s	*all_s;
	double	m_wx;
	double	m_wy;
	int		mouse_x;
	int		mouse_y;

	all_s = context;
	if (xdelta)
		;
	mlx_get_mouse_pos(all_s->vars->mlx, &mouse_x, &mouse_y);
	m_wx = (double)(mouse_x * all_s->g_vars->steps_x - all_s->g_vars->offset_x);
	m_wy = (double)(all_s->g_vars->offset_y - all_s->g_vars->steps_y * mouse_y);
	zoom_util(ydelta, all_s);
	all_s->g_vars->offset_x = m_wx * -1 + all_s->g_vars->steps_x \
		* all_s->vars->win_width / 2;
	all_s->g_vars->offset_y = m_wy * 1 + all_s->g_vars->steps_y \
		* all_s->vars->win_height / 2;
	mlx_set_mouse_pos(all_s->vars->mlx, all_s->vars->win_width / 2, \
		all_s->vars->win_height / 2);
	all_s->calc[all_s->fractal->frac_type](all_s->pxl, all_s);
}

void	mouse_press(mouse_key_t button, action_t act, modifier_key_t m, void *c)
{
	t_all_s	*all_s;
	int		mouse_x;
	int		mouse_y;
	double	m_wx;
	double	m_wy;

	all_s = c;
	if (m)
		;
	if (button == MLX_MOUSE_BUTTON_LEFT && act == MLX_PRESS)
	{
		mlx_get_mouse_pos(all_s->vars->mlx, &mouse_x, &mouse_y);
		m_wx = (double)(mouse_x * all_s->g_vars->steps_x \
			- all_s->g_vars->offset_x);
		m_wy = (double)(all_s->g_vars->offset_y \
			- all_s->g_vars->steps_y * mouse_y);
		all_s->g_vars->offset_x += m_wx;
		all_s->g_vars->offset_y += m_wy * (-1.0);
	}
	all_s->calc[all_s->fractal->frac_type](all_s->pxl, all_s);
}

int	main(int argc, char *argv[])
{
	t_pxl_data		*pxl;
	t_all_s			all_s;
	t_calc			calc[3];

	pxl = (t_pxl_data *)malloc(sizeof(t_pxl_data) * (700 * 700 + 1));
	init_calc(calc);
	all_s.pxl = pxl;
	all_s.calc = calc;
	if (init_vars(&all_s, argv) == ERROR || argc < 2)
	{
		write(1, "mandel\njulia <num> <num>\nbship\n", 31);
		my_exit(all_s);
	}
	if (all_s.fractal->frac_type == JULIA)
		set_julia_vals(all_s, argv);
	calc[all_s.fractal->frac_type](pxl, &all_s);
	mlx_key_hook(all_s.vars->mlx, &my_keyhook, &all_s);
	mlx_mouse_hook(all_s.vars->mlx, &mouse_press, &all_s);
	mlx_scroll_hook(all_s.vars->mlx, &zoom, &all_s);
	mlx_loop_hook(all_s.vars->mlx, &coloring, &all_s);
	mlx_loop(all_s.vars->mlx);
	my_exit(all_s);
	return (0);
}
