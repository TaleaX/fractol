/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:19:22 by tdehne            #+#    #+#             */
/*   Updated: 2022/06/23 13:31:18 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "fractol.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	print_rect(t_img *img, int x, int y, int width, int color)
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

void calc(double c_r, double c_i, double z_r, double z_i, int px, int py, int depth, t_img *img)
{
	double	re;
	double	im;
	int counter;

	counter = 0;
	while (1)
	{
		re = z_r*z_r - z_i*z_i + c_r;
		im = 2*z_r*z_i + c_i;
		//printf("re = %.1f im =  %.1f c_r =  %.1f c_i =  %.1f px = %d py = %d betrag = %.1f\n", re, im, c_r, c_i, px, py, sqrt(re * re + im * im));
		if (counter == depth){
			//printf("in here");
			//mlx_pixel_put(mlx, mlx_win, px, py, 0x00000000);
			//printf("c_r = %.3f c_i = %.3f z_r = %.3f z_i = %.3f smaller 2 \n", c_r, c_i, z_r, z_i);
			img_pix_put(img, px, py, 0x00000000);
			break;
		}
		if (sqrt(re*re + im*im) > 2.0){
			//mlx_pixel_put(mlx, mlx_win, px, py, 0x00FF66FF);
			//printf("c_r = %.3f c_i = %.3f z_r = %.3f z_i = %.3f greater 2 \n", c_r, c_i, z_r, z_i);
			if (counter > 45)
				my_mlx_pixel_put(img, px, py, MAGENTA);
			else if (counter > 40)
				my_mlx_pixel_put(img, px, py, RED);
			else if (counter > 30)
				my_mlx_pixel_put(img, px, py, ROSA);
			else if (counter > 20)
				my_mlx_pixel_put(img, px, py, PURPLE);
			else if (counter > 10)
				my_mlx_pixel_put(img, px, py, BLUE);
			else if (counter > 5)
				my_mlx_pixel_put(img, px, py, LIGHT_PURPLE);
			else
				my_mlx_pixel_put(img, px, py, LIGHT_BLUE);
			break ;
		}
		
		z_r = re;
		z_i = im;
		counter++;
	}
}

int main()
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	double	neg;
	double	pos;
	double	steps_x;
	double	steps_y;
	int		win_width;
	int		win_height;

	mlx = mlx_init();
	win_height = 1300;
	win_width = 1350;
	mlx_win = mlx_new_window(mlx, win_width, win_height, "Hello world!");
	img.img = mlx_new_image(mlx, win_width, win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length, &img.endian);
	neg = -2;
	steps_x =  4.0 / win_width;
	steps_y = 4.0 / win_height;
	//printf("steps = %.3f\n", steps);
	for (int i = 0; i < win_width; i++)
	{
		pos = 2;
		for (int j = 0; j < win_height; j++)
		{
			calc(neg, pos, 0, 0, i, j, 50, &img);
			pos -= steps_y;
		}
		neg += steps_x;
	}
	//print_rect(&img, 100, 100, 20, 0x00FF03DD);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}