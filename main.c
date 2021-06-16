/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 22:36:55 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/15 17:16:50 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void inicializar_variables(t_fractol *fractol)
{
	fractol->mandel.zoom = 1; 
	fractol->mandel.move_x = -0.5;
	fractol->mandel.move_y = 0;
	fractol->mandel.max_iterations = 50; //after how much iterations the function should stop
	fractol->julia.zoom = 1;
	fractol->julia.move_x = 0;
	fractol->julia.move_y = 0; //you can change these to zoom and change position
	fractol->julia.max_iterations = 50; //after how much iterations the function should stop
	//pick some values for the constant c, this determines the shape of the Julia Set
	fractol->julia.c_re = -0.7;
	fractol->julia.c_im = 0.27015;
}

static void	start_fractol(t_fractol *fractol)
{
	fractol->eje_x = 900;
	fractol->eje_y = 700;
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		print_error("Something went wrong with the minilibx");
	fractol->window = mlx_new_window(fractol->mlx, fractol->eje_x, fractol->eje_y, "fract-ol");
	if (!fractol->window)
		print_error("Something went wrong opening the window");
	fractol->img.img = mlx_new_image(fractol->mlx,
			fractol->eje_x, fractol->eje_y);
	fractol->img.addr = mlx_get_data_addr(fractol->img.img, 
			&fractol->img.bits_per_pixel, &fractol->img.line_length,
			&fractol->img.endian);
	mlx_hook(fractol->window, KEY_PRESS, 1L << 0, keys_press, fractol);
	mlx_hook(fractol->window, KEY_RELEASE, 1L << 0, keys_release, fractol);
	mlx_hook(fractol->window, DESTROY_NOTIFY, 0L, destroy, fractol);
	mlx_mouse_hook(fractol->window, scroll_mouse, fractol);
	if (fractol->is_julia)
	{
		inicializar_variables(fractol);
		mlx_loop_hook(fractol->mlx, julia, fractol);
	}
	if (fractol->is_mandelbrot)
	{
		inicializar_variables(fractol);
		mlx_loop_hook(fractol->mlx, mandelbrot, fractol);
	}
	mlx_loop(fractol->mlx);
}

static void	print_list()
{
	printf("You can try with:\n\n   · Julia \n   · Mandelbrot\n");
	exit (0);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	ft_bzero(&fractol, sizeof(t_fractol));
	if (argc < 2 || argc > 2)
		print_list();
	else
	{
		if (ft_strcmp(argv[1], "Mandelbrot")
			|| ft_strcmp(argv[1], "mandelbrot"))
			fractol.is_mandelbrot = 1;
		else if (ft_strcmp(argv[1], "Julia") || ft_strcmp(argv[1], "julia"))
			fractol.is_julia = 1;
		else
			print_list();
		start_fractol(&fractol);
	}
}
