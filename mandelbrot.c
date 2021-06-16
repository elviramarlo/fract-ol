/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:56:06 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/15 16:25:01 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	zoom_keys(t_fractol *fractol)
{
    if(fractol->key.scroll_in)
	{
		fractol->mandel.zoom *= pow(1.001, fractol->mandel.frame_time);
		fractol->key.scroll_in = 0;
	}
    if(fractol->key.scroll_out) 
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
    if(fractol->key.plus)
		fractol->mandel.max_iterations *= 2;
    if(fractol->key.minus)
	{
		if(fractol->mandel.max_iterations > 2)
			fractol->mandel.max_iterations /= 2;
	}
	zoom_keys(fractol);
}

static void	iterations(t_fractol *fractol)
{
	int i;

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
		if((fractol->mandel.new_re * fractol->mandel.new_re
			+ fractol->mandel.new_im * fractol->mandel.new_im) > 4)
			break;
		i++;
	}
	fractol->mandel.color = create_trgb(0, 265, 255, 255)
		* (i < fractol->mandel.max_iterations);
}

int	mandelbrot(t_fractol *fractol)
{
	int x;
	int y;

	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, fractol->window);
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
			fractol->mandel.new_re = 0;
			fractol->mandel.new_im = 0;
			fractol->mandel.old_re = 0;
			fractol->mandel.old_im = 0;
			iterations(fractol);
			my_mlx_pixel_put(&fractol->img, x, y, fractol->mandel.color);
			x++;
		}
		y++;
	}
	move_keys(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->window,
		fractol->img.img, 0, 0);
	return (0);
}
