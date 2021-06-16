/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   c_reated: 2021/06/14 20:38:28 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/15 16:35:48 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	move_keys(t_fractol *fractol)
{
	fractol->julia.frame_time = 50;
	//ZOOM keys
    if(fractol->key.scroll_in)
	{
		fractol->julia.zoom *= pow(1.001, fractol->julia.frame_time);
		fractol->key.scroll_in = 0;
	}
    if(fractol->key.scroll_out)
	{
		fractol->julia.zoom /= pow(1.001, fractol->julia.frame_time);
		fractol->key.scroll_out = 0;
	}
    //MOVE keys
    if(fractol->key.down)
	{
		fractol->julia.move_y += 0.0003 * fractol->julia.frame_time/ fractol->julia.zoom;
	}
    if(fractol->key.up)
	{
		fractol->julia.move_y -= 0.0003 * fractol->julia.frame_time/ fractol->julia.zoom;
	}
    if(fractol->key.right)
	{
		fractol->julia.move_x += 0.0003 * fractol->julia.frame_time/ fractol->julia.zoom;
	}
    if(fractol->key.left)
	{
		fractol->julia.move_x -= 0.0003 * fractol->julia.frame_time/ fractol->julia.zoom;
	}

	if(fractol->key.plus)
		fractol->julia.max_iterations *= 2;
   /*  //CHANGE SHAPE keys
    if(keyDown(SDLK_KP2)) {cIm += 0.0002 * frame_time/ zoom;}
    if(keyDown(SDLK_KP8)) {cIm -= 0.0002 * frame_time/ zoom;}
    if(keyDown(SDLK_KP6)) {cRe += 0.0002 * frame_time/ zoom;}
    if(keyDown(SDLK_KP4)) {cRe -= 0.0002 * frame_time/ zoom;}
    //keys to change number of iterations
    if(keyPressed(SDLK_KP_MULTIPLY)) {maxIterations *= 2;}
    if(keyPressed(SDLK_KP_DIVIDE))   {if(maxIterations > 2) maxIterations /= 2;}
    //key to change the text options
    if(keyPressed(SDLK_F1)) {showText++; showText %= 3;} */
}

int	julia(t_fractol *fractol)
{
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, fractol->window);
  //loop through every pixel
  for(int y = 0; y < fractol->eje_y; y++)
  for(int x = 0; x < fractol->eje_x; x++)
  {
    //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
    fractol->julia.new_re = 1.5 * (x - fractol->eje_x / 2) / (0.5 * fractol->julia.zoom * fractol->eje_x) + fractol->julia.move_x;
    fractol->julia.new_im = (y - fractol->eje_y / 2) / (0.5 * fractol->julia.zoom * fractol->eje_y) + fractol->julia.move_y;
    //i will represent the number of iterations
    int i;
    //start the iteration process
    for(i = 0; i < fractol->julia.max_iterations; i++)
    {
      //remember value of previous iteration
    	fractol->julia.old_re = fractol->julia.new_re;
    	fractol->julia.old_im = fractol->julia.new_im;
      //the actual iteration, the real and imaginary part are calculated
      fractol->julia.new_re = fractol->julia.old_re * fractol->julia.old_re - fractol->julia.old_im * fractol->julia.old_im + fractol->julia.c_re;
      fractol->julia.new_im = 2 * fractol->julia.old_re * fractol->julia.old_im + fractol->julia.c_im;
      //if the point is outside the circle with radius 2: stop
      if((fractol->julia.new_re * fractol->julia.new_re + fractol->julia.new_im * fractol->julia.new_im) > 4)
	  		break;
    }
    //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
    fractol->julia.color = create_trgb(0, 205, 105, 255)
		* (i < fractol->julia.max_iterations);
	my_mlx_pixel_put(&fractol->img, x, y, fractol->julia.color);
    //draw the pixel
    //pset(x, y, fractol->julia.color);
  }
  //make the Julia Set visible and wait to exit
  /* redraw();
  sleep(); */
 	move_keys(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->window, fractol->img.img, 0, 0);
	return (0);
}