/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:44:27 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/28 12:20:01 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_for_color(t_all_s *all_s)
{
	if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_1))
		all_s->vars->color_width += 0.25;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_2))
		all_s->vars->color_width -= 0.25;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_3))
		all_s->vars->color_offset += 0.25;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_4))
		all_s->vars->color_offset -= 0.25;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_R))
		all_s->vars->color_reverse ^= 1;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_N))
		all_s->color->shift ^= 1;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_5))
		all_s->color->max_value += 10;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_6))
		all_s->color->max_value -= 10;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_D))
		all_s->color->dynamic_max ^= 1;
	else
		return (0);
	if (all_s->color->max_value <= 0)
		all_s->color->max_value = 10;
	return (1);
}

int	key_for_move(t_all_s *all_s)
{
	if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_RIGHT))
		all_s->g_vars->offset_x += 0.1 * all_s->g_vars->steps_x \
			* all_s->vars->win_width;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_LEFT))
		all_s->g_vars->offset_x -= 0.1 * all_s->g_vars->steps_x \
			* all_s->vars->win_width;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_UP))
		all_s->g_vars->offset_y -= 0.1 * all_s->g_vars->steps_y \
			* all_s->vars->win_height;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_DOWN))
		all_s->g_vars->offset_y += 0.1 * all_s->g_vars->steps_y \
			* all_s->vars->win_height;
	else
		return (0);
	return (1);
}

int	key_core(t_all_s *all_s)
{
	if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_A))
		all_s->vars->iter_depth += 50;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_S))
		all_s->vars->iter_depth -= 50;
	else if (all_s->vars->iter_depth <= 0)
		all_s->vars->iter_depth = 50;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_J))
		all_s->fractal->frac_type = JULIA;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_M))
		all_s->fractal->frac_type = MANDEL;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_B))
		all_s->fractal->frac_type = BSHIP;
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_ESCAPE))
		my_exit(*all_s);
	else if (mlx_is_key_down(all_s->vars->mlx, MLX_KEY_Q))
		reset(*all_s);
	else
		return (0);
	if (all_s->vars->iter_depth <= 0)
		all_s->vars->iter_depth = 50;
	return (1);
}
