/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:12:00 by tdehne            #+#    #+#             */
/*   Updated: 2022/08/25 18:18:42 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_exit(t_all_s all_s)
{
	free(all_s.pxl);
	mlx_terminate(all_s.vars->mlx);
	all_s.pxl = NULL;
	system("leaks a.out");
	exit(0);
}
