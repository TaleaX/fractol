/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/09 18:39:49 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"

typedef struct s_loop {
	t_graphic_vars 	*g_vars;
	t_pxl_data 		*pxl;
	t_vars			*vars;
	t_img			*img;
	t_mandel		*mandel;
	int				mouse_x;
	int				mouse_y;
} t_loop;

void test(void *context){
	t_loop	*loop = context;
	t_pxl_data	*tmp;

	(loop->g_vars->count)++;
	tmp = loop->pxl;
	while (tmp->px != -1)
	{
		if (tmp->counter == 50)
		{
			mlx_put_pixel(loop->img->img, tmp->px, tmp->py, 0x000000FF);
		}
		else
		{
			mlx_put_pixel(loop->img->img, tmp->px, tmp->py, color(tmp->counter, 50, 5 * M_PI / 3 + sin(loop->g_vars->count / 20.0) + 1, sin(loop->g_vars->count / 20.0) + 1, 0));
		}
		(tmp)++;
	}
	//mlx_get_mouse_pos(loop->vars->mlx, &loop->mouse_x, &loop->mouse_y);
	mlx_image_to_window(loop->vars->mlx, loop->img->img, 0, 0);
}

void my_keyhook(mlx_key_data_t keydata, void* context)
{
	t_loop	*loop = context;
	// If we PRESS the 'J' key, print "Hello".
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		loop->g_vars->w_x -= 0.02;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		loop->g_vars->w_x += 0.02;
	}
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		loop->g_vars->w_y += 0.02;
	}
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		loop->g_vars->w_y -= 0.02;
		
	}
	make_mandel(loop->pxl, loop->g_vars, loop->vars, loop->mandel);
}

void mouse_press(mouse_key_t button, action_t action, modifier_key_t mods, void* context)
{
	t_loop	*loop = context;
	float	m_wx;
	float	m_wy;
		
	if (mlx_is_mouse_down(loop->vars->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(loop->vars->mlx, &loop->mouse_x, &loop->mouse_y);
		m_wx = loop->g_vars->steps_x * loop->mouse_x + loop->g_vars->w_x;
		m_wy = (loop->mouse_y < loop->vars->win_height / 2) ? (loop->g_vars->w_y - loop->g_vars->steps_y * loop->mouse_y) : -(loop->g_vars->steps_y * loop->mouse_y - loop->g_vars->w_y);
		printf("%lf %lf %d %d %lf %lf\n", m_wx, m_wy, loop->mouse_x, loop->mouse_y, loop->g_vars->w_y, loop->g_vars->w_x);
		if (m_wx < 0)
			loop->g_vars->offset_x += m_wx * (-1.0);
		else
			loop->g_vars->offset_x += m_wx * (-1.0);
		if (m_wy < 0)
			loop->g_vars->offset_y += m_wy * (-1.0);
		else
			loop->g_vars->offset_y += m_wy * (-1.0);
	}
	make_mandel(loop->pxl, loop->g_vars, loop->vars, loop->mandel);
	printf("%lf %lf %d %d %lf %lf\n", m_wx, m_wy, loop->mouse_x, loop->mouse_y, loop->g_vars->w_y, loop->g_vars->w_x);
}

float	abs_f(float num)
{
	if (num < 0)
		return (-num);
	return (num);
}
void	zoom(double xdelta, double ydelta, void* context)
{
	t_loop	*loop = context;
	float	m_wx;
	float	m_wy;
	float	offset_x;
	float	offset_y;

	mlx_get_mouse_pos(loop->vars->mlx, &loop->mouse_x, &loop->mouse_y);
	m_wx = loop->g_vars->steps_x * loop->mouse_x + loop->g_vars->w_x;
	m_wy = (loop->mouse_y < loop->vars->win_height / 2) ? (loop->g_vars->w_y - loop->g_vars->steps_y * loop->mouse_y) : -(loop->g_vars->steps_y * loop->mouse_y - loop->g_vars->w_y);
	
	

	if (ydelta > 0)
	{
		//loop->g_vars->offset_x -= ((float)loop->mouse_x / loop->vars->win_width);
		//loop->g_vars->offset_y -= ((float)loop->mouse_y / loop->vars->win_height);
		loop->g_vars->zoom -= 0.1;
	}
	else
	{
		//loop->g_vars->offset_x += ((float)loop->mouse_x / loop->vars->win_width);
		//loop->g_vars->offset_y += ((float)loop->mouse_y / loop->vars->win_height);
		loop->g_vars->zoom += 0.1;
	}
	
	make_mandel(loop->pxl, loop->g_vars, loop->vars, loop->mandel);
}

int main()
{
	t_img			img;
	t_mandel		mandel;
	t_vars			vars;
	t_graphic_vars	g_vars;
	t_loop			loop;
	t_pxl_data		*pxl;
	int				count;

	pxl = (t_pxl_data *)malloc(sizeof(t_pxl_data) * (700 * 700 + 1));
	count = 0;
	loop.mouse_x = 0;
	loop.mouse_y = 0;
	g_vars.count = 0;
	
	vars.win_height = 600;
	vars.win_width = 600;
	g_vars.w_x = -2;
	g_vars.w_y = 2;
	g_vars.zoom = 1;
	g_vars.offset_x = 2;
	g_vars.offset_y = 2;
	loop.g_vars = &g_vars;
	loop.pxl = pxl;
	loop.mandel = &mandel;
	vars.mlx = mlx_init(vars.win_width, vars.win_height, "FRACTOL", 1);
	img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	loop.img = &img;
	loop.vars = &vars;
	make_mandel(pxl, &g_vars, &vars, &mandel);
	mlx_loop_hook(vars.mlx, &test, &loop);
	//mlx_key_hook(vars.mlx, &my_keyhook, &loop);
	mlx_scroll_hook(vars.mlx, &zoom, &loop);
	mlx_mouse_hook(vars.mlx, &mouse_press, &loop);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}