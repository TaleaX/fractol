/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:19:35 by tdehne            #+#    #+#             */
/*   Updated: 2022/05/22 15:22:03 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_rect(t_data *img, int x, int y, int width, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i++ <= width)
	{
		j = 0;
		while (j++ <= width)
			my_mlx_pixel_put(img, x + i, y + j, color);
	}
}

/*void calc(double re_a, double im_b, double re_c, double im_d, int depth, int* counter, t_data *img)
{
	double	re;
	double	im;

	re = re_c*re_c - im_d*im_d + re_a;
	im = 2*re_c*im_d + im_b;
	printf("betrag = %.1f\n", sqrt(re*re - im*im));
	if (sqrt(re*re - im*im) > 2){
		my_mlx_pixel_put(img, re_a, im_b, 0x00FF66FF);
		return ;
	}
	if (*counter == depth){
		printf("in here");
		my_mlx_pixel_put(img, re_a, im_b, 0x00000000);
		return ;
	}
	(*counter)++;
	calc(re_a, im_b, re, im, depth, counter, img);
}*/

void calc(double re_a, double im_b, double re_c, double im_d, int depth, int px, int py)
{
	double	re;
	double	im;
	int counter;

	counter = 0;
	while (1)
	{
		re = re_c*re_c - im_d*im_d + re_a;
		im = 2*re_c*im_d + im_b;
		printf("re = %.1f im =  %.1f re_a =  %.1f im_b =  %.1f px = %d py = %d betrag = %.1f\n", re, im, re_a, im_b, px, py, sqrt(re * re + im * im));
		if (sqrt(re*re + im*im) > 2.0){
			printf("greater 2 \n");
			break ;
		}
		if (counter == depth){
			printf("in here");
			break;
		}
		re_c = re;
		im_d = im;
		counter++;
	}
}

int main()
{
	/*void	*mlx;
	t_data	img;
	void	*mlx_win;*/
	int		win_width;
	int		win_height;
	double	neg;
	double	pos;
	double	steps;

	win_width = 400;
	win_height = 400;
	/*mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, win_width, win_height, "Hello world!");
	img.img = mlx_new_image(mlx, 10, 10);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);*/
	
	//mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	neg = -2;
	steps = 1.0 / (win_height / 4);
	printf("steps = %.3f\n", steps);
	for (int i = 0; i < win_width; i++)
	{
		pos = 2;
		for (int j = 0; j < win_height; j++)
		{
			calc(neg, pos, 0, 0, 10, i, j);
			pos -= steps;	
		}
		neg += steps;
	}
	/*calc(1, 0, 0, 0, 50, &counter, &img);
	printf("%d\n", counter);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);*/
	return (0);
}