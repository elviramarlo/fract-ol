/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:48:12 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/22 15:59:47 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_keys(t_fractol *fractol)
{
	if (fractol->key.scroll_in)
	{
		fractol->julia.zoom *= pow(1.001, fractol->julia.frame_time);
		fractol->key.scroll_in = 0;
	}
	if (fractol->key.scroll_out)
	{
		fractol->julia.zoom /= pow(1.001, fractol->julia.frame_time);
		fractol->key.scroll_out = 0;
	}
	if (fractol->key.z)
		fractol->julia.c_re = fractol->julia.c_re - 0.02;
	if (fractol->key.x)
		fractol->julia.c_re = fractol->julia.c_re + 0.02;
}

static void	move_keys(t_fractol *fractol)
{
	fractol->julia.frame_time = 200;
	if (fractol->key.down)
		fractol->julia.move_y += 0.0003 * fractol->julia.frame_time
			/ fractol->julia.zoom;
	if (fractol->key.up)
		fractol->julia.move_y -= 0.0003 * fractol->julia.frame_time
			/ fractol->julia.zoom;
	if (fractol->key.right)
		fractol->julia.move_x += 0.0003 * fractol->julia.frame_time
			/ fractol->julia.zoom;
	if (fractol->key.left)
		fractol->julia.move_x -= 0.0003 * fractol->julia.frame_time
			/ fractol->julia.zoom;
	if (fractol->key.plus)
		fractol->julia.max_iterations *= 2;
	if (fractol->key.minus)
	{
		if (fractol->julia.max_iterations > 2)
			fractol->julia.max_iterations /= 2;
	}
	zoom_keys(fractol);
}

static void	put_color(t_fractol *fractol, int i, int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255 * ((double)i / (double)fractol->julia.max_iterations));
	g = ((255 - r)) * fabs(sin(2));
	b = ((255 - r)) * fabs(cos(4));
	fractol->julia.color = create_trgb(0, r * 2, g
			* asin((double)fractol->julia.max_iterations),
			b * (double)fractol->julia.max_iterations)
		* (i < fractol->julia.max_iterations);
	my_mlx_pixel_put(&fractol->img, x, y, fractol->julia.color);
}

/*
** newz = oldz * oldz + c
*/

static void	iterations(t_fractol *fractol, int x, int y)
{
	int	i;

	fractol->julia.new_re = 1.5 * (x - fractol->eje_x / 2)
		/ (0.5 * fractol->julia.zoom * fractol->eje_x)
		+ fractol->julia.move_x;
	fractol->julia.new_im = (y - fractol->eje_y / 2)
		/ (0.5 * fractol->julia.zoom * fractol->eje_y)
		+ fractol->julia.move_y;
	i = 0;
	while (i < fractol->julia.max_iterations)
	{
		fractol->julia.old_re = fractol->julia.new_re;
		fractol->julia.old_im = fractol->julia.new_im;
		fractol->julia.new_re = fractol->julia.old_re
			* fractol->julia.old_re - fractol->julia.old_im
			* fractol->julia.old_im + fractol->julia.c_re;
		fractol->julia.new_im = 2 * fractol->julia.old_re
			* fractol->julia.old_im + fractol->julia.c_im;
		if ((fractol->julia.new_re * fractol->julia.new_re
				+ fractol->julia.new_im * fractol->julia.new_im) > 4)
			break ;
		i++;
	}
	put_color(fractol, i, x, y);
}

int	julia(t_fractol *fractol)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, fractol->window);
	while (y < fractol->eje_y)
	{
		x = 0;
		while (x < fractol->eje_x)
		{
			iterations(fractol, x, y);
			x++;
		}
		y++;
	}
	move_keys(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->window,
		fractol->img.img, 0, 0);
	return (0);
}
