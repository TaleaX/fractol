/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/07 17:55:42 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"



int	key_hook(int keycode)
{
	printf("Hello from key_hook! %d\n", keycode);
	return (0);
}

typedef struct s_loop {
	t_graphic_vars 	*g_vars;
	t_pxl_data 		*pxl;
	t_vars			*vars;
	t_img			*img;
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
	mlx_get_mouse_pos(loop->vars->mlx, &loop->mouse_x, &loop->mouse_y);
	mlx_image_to_window(loop->vars->mlx, loop->img->img, 0, 0);
}

int mouse_hook(int mousecode, t_graphic_vars *g_vars)
{
	if (mousecode == 2)
		g_vars->zoom = 1.5;
	return 0;
}

int main()
{
	t_img			img;
	
	t_vars			vars;
	t_graphic_vars	g_vars;
	t_loop			loop;
	t_pxl_data		*pxl;
	int				count;

	pxl = (t_pxl_data *)malloc(sizeof(t_pxl_data) * (600 * 600 + 1));
	count = 0;
	loop.mouse_x = 0;
	loop.mouse_y = 0;
	g_vars.count = 0;
	g_vars.zoom = 1;
	g_vars.win_height = 600;
	g_vars.win_width = 600;
	loop.g_vars = &g_vars;
	loop.pxl = pxl;
	vars.mlx = mlx_init(g_vars.win_width, g_vars.win_height, "FRACTOL", 1);
	//vars.win = mlx_new_image(vars.mlx, g_vars.win_width, g_vars.win_height);
	img.img = mlx_new_image(vars.mlx, g_vars.win_width, g_vars.win_height);
	//img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	loop.img = &img;
	loop.vars = &vars;
	make_mandel(pxl, &g_vars);
	//print_rect(&img, 100, 100, 20, 0x00FF03DD);
	
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	
	mlx_loop_hook(vars.mlx, &test, &loop);
	
	mlx_loop(vars.mlx);
	return (0);
}