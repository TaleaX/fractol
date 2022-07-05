/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/07/05 13:28:47 by tdehne           ###   ########.fr       */
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
	t_vars 	*vars;
	t_img 	*img;
} t_loop;

int test(t_loop *loop){
	(loop->vars->count)++;
	make_mandel(loop->vars, loop->img);
	mlx_put_image_to_window(loop->vars->mlx, loop->vars->win, loop->img->img, 0, 0);
	return 0;
}

int mouse_hook(int mousecode, t_vars *vars)
{
	if (mousecode == 2)
		vars->zoom = 1.1;
	return 0;
}

int main()
{
	t_img	img;
	
	t_vars	vars;
	t_loop	loop;

	vars.mlx = mlx_init();
	vars.win_height = 600;
	vars.win_width = 600;
	vars.count = 0;
	vars.zoom = 1.1;
	loop.vars = &vars;
	loop.img = &img;
	vars.win = mlx_new_window(vars.mlx, vars.win_width, vars.win_height, "Hello world!");
	img.img = mlx_new_image(vars.mlx, vars.win_width, vars.win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	//print_rect(&img, 100, 100, 20, 0x00FF03DD);
	
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	
	mlx_loop_hook(vars.mlx, test, &loop);
	mlx_loop(vars.mlx);
	return (0);
}