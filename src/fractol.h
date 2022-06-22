/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdehne <tdehne@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 07:24:48 by tdehne            #+#    #+#             */
/*   Updated: 2022/06/22 13:24:13 by tdehne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define MAGENTA 0xFF00FF
# define RED 0xd44275
# define PURPLE 0xc034eb
# define BLUE 0x4e42d4
# define LIGHT_BLUE 0x42cad4
# define LIGHT_PURPLE 0x288f2
# define ROSA 0xe58feb

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;


#endif