/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/23 17:36:04 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"



void test(void *context){
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
		else
		{
			if (tmp->px < all_s->vars->win_width && tmp->px >= 0 && tmp->py < all_s->vars->win_height && tmp->py >= 0)
				mlx_put_pixel(all_s->img->img, tmp->px, tmp->py, color(tmp->counter, 500, 5 * M_PI / 3 + sin(all_s->g_vars->count / 20.0) + 1, sin(all_s->g_vars->count / 20.0) + 1, 1));
		}
		(tmp)++;
	}
	mlx_image_to_window(all_s->vars->mlx, all_s->img->img, 0, 0);
}

void my_keyhook(mlx_key_data_t keydata, void* context)
{
	t_all_s	*all_s = context;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_x += 0.2;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_x -= 0.2;
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_y -= 0.2;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		all_s->g_vars->offset_y += 0.2;
		
	}
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		all_s->vars->iter_depth += 50;
	if (keydata.key == MLX_KEY_B && keydata.action == MLX_PRESS)
		all_s->vars->iter_depth -= 50;
	make_mandel(all_s->pxl, all_s->g_vars, all_s->vars, all_s->fractal, all_s);
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
	make_mandel(all_s->pxl, all_s->g_vars, all_s->vars, all_s->fractal, all_s);
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
	make_mandel(all_s->pxl, all_s->g_vars, all_s->vars, all_s->fractal, all_s);
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

int main(int argc, char *argv[])
{
	t_img			img;
	t_vars			vars;
	t_fractals		fractal;
	t_graphic_vars	g_vars;
	t_all_s			all_s;
	t_pxl_data		*pxl;
	int				count;

	pxl = (t_pxl_data *)malloc(sizeof(t_pxl_data) * (700 * 700 + 1));
	count = 0;
	g_vars.count = 0;
	
	vars.win_height = 600;
	vars.win_width = 600;
	g_vars.offset_x = 2;
	g_vars.offset_y = 2;
	g_vars.s_x = 0;
	g_vars.s_y = 0;
	g_vars.w_x = 0.0;
	g_vars.w_y = 0.0;
	pxl->px = 0;
	pxl->py = 0;
	pxl->wx = 0.0;
	pxl->wy = 0.0;
	g_vars.steps_x = 4.0 / vars.win_width;
	g_vars.steps_y = 4.0 / vars.win_height;
	vars.iter_depth = 50;
	all_s.g_vars = &g_vars;
	all_s.pxl = pxl;
	all_s.fractal = &fractal;
	vars.mlx = mlx_init(vars.win_width, vars.win_height, "FRACTOL", 1);
	img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	all_s.img = &img;
	all_s.vars = &vars;
	/*if (argc > 2)
	{
		fractal.c_r = atof(argv[1]);
		fractal.c_i = atof(argv[2]);
		make_julia(pxl, &g_vars, &vars, &fractal, &all_s);
		printf("%s\n", argv[1]);
	}*/
	make_mandel(pxl, &g_vars, &vars, &fractal, &all_s);
	mlx_key_hook(vars.mlx, &my_keyhook, &all_s);
	// mlx_mouse_hook(vars.mlx, &mouse_press, &all_s);
	mlx_scroll_hook(vars.mlx, &zoom, &all_s);
	mlx_loop_hook(vars.mlx, &test, &all_s);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}