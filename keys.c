/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 18:45:36 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/15 16:27:40 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	destroy()
{
	exit (0);
	return (0);
}

int	keys_release(int tecla, t_fractol *fractol)
{
	if (tecla == K_UP || tecla == K_W)
		fractol->key.up = 0;
	if (tecla == K_DOWN || tecla == K_S)
		fractol->key.down = 0;
	if (tecla == K_RIGHT  || tecla == K_D)
		fractol->key.right = 0;
	if (tecla == K_LEFT  || tecla == K_A)
		fractol->key.left = 0;
	if (tecla == K_PLUS)
		fractol->key.plus = 0;
	if (tecla == K_MINUS)
		fractol->key.minus = 0;
	return (tecla);
}

int	keys_press(int tecla, t_fractol *fractol)
{
	if (tecla == K_UP || tecla == K_W)
		fractol->key.up = 1;
	if (tecla == K_DOWN  || tecla == K_S)
		fractol->key.down = 1;
	if (tecla == K_RIGHT || tecla == K_D)
		fractol->key.right = 1;
	if (tecla == K_LEFT  || tecla == K_A)
		fractol->key.left = 1;
	if (tecla == K_PLUS)
		fractol->key.plus = 1;
	if (tecla == K_MINUS)
		fractol->key.minus = 1;
	if (tecla == K_ESC)
		destroy();
	//printf("TECLA=%d\n", tecla);
	return (tecla);
}

int	scroll_mouse(int tecla, int x, int y, t_fractol *fractol)
{
	x = 1;;
	y = 1;
	if (tecla == SCROLL_DOWN)
		fractol->key.scroll_out = 1;
	if (tecla == SCROLL_UP)
		fractol->key.scroll_in = 1;
	return (0);
}
