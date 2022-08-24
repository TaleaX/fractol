/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/24 18:15:56 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"

static void coloring(void *context){
	t_all_s	*all_s = context;
	t_pxl_data	*tmp;

	(all_s->g_vars->count)++;
	tmp = all_s->pxl;
	while (tmp->px != -1)
	{
		if (tmp->counter == all_s->vars->iter_depth)
		{
			if (tmp->px < all_s->vars->win_width && tmp->px >= 0 && tmp->py < all_s->vars->win_height && tmp->py >= 0)
				mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, 0x000000FF);
		}
		else if (all_s->fractal->frac_type == MANDEL || all_s->fractal->frac_type == JULIA)
		{
			if (tmp->px < all_s->vars->win_width && tmp->px >= 0 && tmp->py < all_s->vars->win_height && tmp->py >= 0)
				mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, color(tmp->counter, 50, all_s->vars->color_width * M_PI / 3 + sin(all_s->g_vars->count / 20.0) + 1, all_s->vars->color_offset * M_PI / 3 + sin(all_s->g_vars->count / 20.0) + 1, all_s->vars->color_reverse));
		}
		else if (all_s->fractal->frac_type == BSHIP)
		{
			if (tmp->px < all_s->vars->win_width && tmp->px >= 0 && tmp->py < all_s->vars->win_height && tmp->py >= 0)
				mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, color(tmp->counter, all_s->vars->iter_depth, all_s->vars->color_width * M_PI / 3, all_s->vars->color_offset * M_PI / 3, all_s->vars->color_reverse));
		}
		(tmp)++;
	}
	mlx_image_to_window(all_s->vars->mlx, all_s->img->img, 0, 0);
}

void my_keyhook(mlx_key_data_t keydata, void* context)
{
	t_all_s	*all_s = context;

	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		all_s->g_vars->offset_x += 0.1 * all_s->g_vars->steps_x * all_s->vars->win_width;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		all_s->g_vars->offset_x -= 0.1 * all_s->g_vars->steps_x * all_s->vars->win_width;
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		all_s->g_vars->offset_y -= 0.1 * all_s->g_vars->steps_y * all_s->vars->win_height;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		all_s->g_vars->offset_y += 0.1 * all_s->g_vars->steps_y * all_s->vars->win_height;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		all_s->vars->iter_depth += 50;
	else if (keydata.key == MLX_KEY_B && keydata.action == MLX_PRESS)
		all_s->vars->iter_depth -= 50;
	else if (keydata.key == MLX_KEY_1 && keydata.action == MLX_PRESS)
		all_s->vars->color_width += 1;
	else if (keydata.key == MLX_KEY_2 && keydata.action == MLX_PRESS)
		all_s->vars->color_width -= 1;
	else if (keydata.key == MLX_KEY_3 && keydata.action == MLX_PRESS)
		all_s->vars->color_offset += 1;
	else if (keydata.key == MLX_KEY_4 && keydata.action == MLX_PRESS)
		all_s->vars->color_offset -= 1;
	else if (keydata.key == MLX_KEY_J && keydata.action == MLX_PRESS)
		all_s->fractal->frac_type = JULIA;
	else if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		all_s->fractal->frac_type = MANDEL;
	else if (keydata.key == MLX_KEY_B && keydata.action == MLX_PRESS)
		all_s->fractal->frac_type = BSHIP;
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(all_s->vars->mlx);
		exit(0);
	}
	else
		return ;	
	all_s->calc[all_s->fractal->frac_type](all_s->pxl, all_s);
}

void mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void* context)
{
	t_all_s	*all_s = context;
	double	m_wx;
	double	m_wy;
	int		mouse_x;
	int		mouse_y;
		
	if (mlx_is_mouse_down(all_s->vars->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(all_s->vars->mlx, &mouse_x, &mouse_y);
		m_wx = (double)(mouse_x * all_s->g_vars->steps_x - all_s->g_vars->offset_x);
		m_wy = (double)(all_s->g_vars->offset_y - all_s->g_vars->steps_y * mouse_y);
		printf("%.3f %.3f\n", all_s->g_vars->steps_x, all_s->g_vars->steps_y);
		all_s->g_vars->steps_x *= 0.9;
		all_s->g_vars->steps_y *= 0.9;
		all_s->g_vars->offset_x = m_wx * -1 + all_s->g_vars->steps_x * all_s->vars->win_width / 2;
		all_s->g_vars->offset_y = m_wy * 1  + all_s->g_vars->steps_y * all_s->vars->win_height / 2;
	}
	all_s->calc[all_s->fractal->frac_type](all_s->pxl, all_s);
}

void	zoom(double xdelta, double ydelta, void* context)
{
	t_all_s	*all_s = context;
	double	m_wx;
	double	m_wy;
	int		mouse_x;
	int		mouse_y;

	mlx_get_mouse_pos(all_s->vars->mlx, &mouse_x, &mouse_y);
	m_wx = (double)(mouse_x * all_s->g_vars->steps_x - all_s->g_vars->offset_x);
	m_wy = (double)(all_s->g_vars->offset_y - all_s->g_vars->steps_y * mouse_y);
	if (ydelta > 0)
	{
		all_s->g_vars->steps_x *= 0.9;
		all_s->g_vars->steps_y *= 0.9;
		all_s->g_vars->offset_x = m_wx * -1 + all_s->g_vars->steps_x * all_s->vars->win_width / 2;
		all_s->g_vars->offset_y = m_wy * 1  + all_s->g_vars->steps_y * all_s->vars->win_height / 2;
	}
	else
	{
		all_s->g_vars->steps_x *= 1.1;
		all_s->g_vars->steps_y *= 1.1;
		all_s->g_vars->offset_x = m_wx * -1 + all_s->g_vars->steps_x * all_s->vars->win_width / 2;
		all_s->g_vars->offset_y = m_wy * 1  + all_s->g_vars->steps_y * all_s->vars->win_height / 2;
	}
	mlx_set_mouse_pos(all_s->vars->mlx, all_s->vars->win_width / 2, all_s->vars->win_height / 2);
	all_s->calc[all_s->fractal->frac_type](all_s->pxl, all_s);
}

/*void mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void* context)
{
	t_all_s	*all_s = context;
	int	m_sx;
	int	m_sy;

	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(all_s->vars->mlx, &m_sx, &m_sy);
		screen_to_world(&all_s->g_vars->m_wx_start, &all_s->g_vars->m_wy_start, m_sx, m_sy, all_s->g_vars);
		all_s->g_vars->offset_x += all_s->g_vars->m_wx_start;
		all_s->g_vars->offset_y += all_s->g_vars->m_wy_start * (-1.0);
	}
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(all_s->vars->mlx, &all_s->g_vars->m_sx, &all_s->g_vars->m_sy);
		
	}
	make_mandel(all_s->pxl, all_s->g_vars, all_s->vars, all_s->mandel, all_s);
}*/

void	decide_algo(t_all_s all_s, char **argv)
{
	if (all_s.fractal->frac_type == JULIA)
	{
		all_s.fractal->c_r = atof(argv[2]);
		all_s.fractal->c_i = atof(argv[3]);
	}
}

int	main(int argc, char *argv[])
{
	t_pxl_data		*pxl;
	t_all_s			all_s;
	t_img			img;
	t_vars			vars;
	t_fractals		fractal;
	t_graphic_vars	g_vars;
	t_calc			calc[3] = {make_mandel, make_julia, make_bship};

	pxl = (t_pxl_data *)malloc(sizeof(t_pxl_data) * (700 * 700 + 1));
	/**/
	all_s.pxl = pxl;
	all_s.img = &img;
	all_s.vars = &vars;
	all_s.g_vars = &g_vars;
	all_s.fractal = &fractal;
	all_s.calc = calc;
	if (init_vars(all_s, argv) == ERROR)
	{
		mlx_terminate(all_s.vars->mlx);
		write(1, "mandel\njulia <num> <num>\nbship\n", 31);
		return (0);
	}
	if (all_s.fractal->frac_type == JULIA)
	{
		if (!argv[2] || !argv[3])
		{
			write(1, "mandel\njulia <num> <num>\nbship\n", 31);
			mlx_terminate(all_s.vars->mlx);
			return (0);
		}
		all_s.fractal->c_r = atof(argv[2]);
		all_s.fractal->c_i = atof(argv[3]);
	}
	calc[all_s.fractal->frac_type](pxl, &all_s);
	mlx_key_hook(all_s.vars->mlx, &my_keyhook, &all_s);
	// mlx_mouse_hook(vars.mlx, &mouse_press, &all_s);
	mlx_scroll_hook(all_s.vars->mlx, &zoom, &all_s);
	mlx_loop_hook(all_s.vars->mlx, &coloring, &all_s);
	mlx_loop(all_s.vars->mlx);
	mlx_terminate(all_s.vars->mlx);
	return (EXIT_SUCCESS);
}
