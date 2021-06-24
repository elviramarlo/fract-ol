/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:56:06 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/21 17:54:20 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_keys(t_fractol *fractol)
{
	if (fractol->key.scroll_in)
	{
		fractol->mandel.zoom *= pow(1.001, fractol->mandel.frame_time);
		fractol->key.scroll_in = 0;
	}
	if (fractol->key.scroll_out)
	{
		fractol->mandel.zoom /= pow(1.001, fractol->mandel.frame_time);
		fractol->key.scroll_out = 0;
	}
}

static void	move_keys(t_fractol *fractol)
{
	fractol->mandel.frame_time = 120;
	if (fractol->key.down)
		fractol->mandel.move_y += 0.0003 * fractol->mandel.frame_time
			/ fractol->mandel.zoom;
	if (fractol->key.up)
		fractol->mandel.move_y -= 0.0003 * fractol->mandel.frame_time
			/ fractol->mandel.zoom;
	if (fractol->key.right)
		fractol->mandel.move_x += 0.0003 * fractol->mandel.frame_time
			/ fractol->mandel.zoom;
	if (fractol->key.left)
		fractol->mandel.move_x -= 0.0003 * fractol->mandel.frame_time
			/ fractol->mandel.zoom;
	if (fractol->key.plus)
		fractol->mandel.max_iterations *= 2;
	if (fractol->key.minus)
	{
		if (fractol->mandel.max_iterations > 2)
			fractol->mandel.max_iterations /= 2;
	}
	zoom_keys(fractol);
}

static void	put_color(t_fractol *fractol, int i, int x, int y)
{
	int	r;
	int	g;
	int	b;

	r = (int)(255 * ((double)i / (double)fractol->mandel.max_iterations));
	g = ((255 - r)) * fabs(sin(2));
	b = ((255 - r)) * fabs(cos(4));
	fractol->mandel.color = create_trgb(0, r, g
			* asin((double)fractol->mandel.max_iterations),
			b * (double)fractol->mandel.max_iterations)
		* (i < fractol->mandel.max_iterations);
	my_mlx_pixel_put(&fractol->img, x, y, fractol->mandel.color);
}

static void	iterations(t_fractol *fractol, int x, int y)
{
	int	i;

	fractol->mandel.new_re = 0;
	fractol->mandel.new_im = 0;
	fractol->mandel.old_re = 0;
	fractol->mandel.old_im = 0;
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, fractol->window);
	i = 0;
	while (i < fractol->mandel.max_iterations)
	{
		fractol->mandel.old_re = fractol->mandel.new_re;
		fractol->mandel.old_im = fractol->mandel.new_im;
		fractol->mandel.new_re = fractol->mandel.old_re
			* fractol->mandel.old_re - fractol->mandel.old_im
			* fractol->mandel.old_im + fractol->mandel.pr;
		fractol->mandel. new_im = 2 * fractol->mandel.old_re
			* fractol->mandel.old_im + fractol->mandel.pi;
		if ((fractol->mandel.new_re * fractol->mandel.new_re
				+ fractol->mandel.new_im * fractol->mandel.new_im) > 4)
			break ;
		i++;
	}
	put_color(fractol, i, x, y);
}

int	mandelbrot(t_fractol *fractol)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < fractol->eje_y)
	{
		x = 0;
		while (x < fractol->eje_x)
		{
			fractol->mandel.pr = 1.5 * (x - fractol->eje_x / 2)
				/ (0.5 * fractol->mandel.zoom * fractol->eje_x)
				+ fractol->mandel.move_x;
			fractol->mandel.pi = (y - fractol->eje_y / 2)
				/ (0.5 * fractol->mandel.zoom * fractol->eje_y)
				+ fractol->mandel.move_y;
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
