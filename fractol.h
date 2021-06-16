/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvmarti <elvmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 22:38:12 by elvmarti          #+#    #+#             */
/*   Updated: 2021/06/15 16:44:10 by elvmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "mlx/mlx.h"

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

# define K_ESC 53
# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_LEFT 123
# define K_RIGHT 124
# define K_DOWN 125
# define K_UP 126
# define K_PLUS		30
# define K_MINUS	44
# define SCROLL_UP		4
# define SCROLL_DOWN	5

/*
** X11 Events
*/
# define KEY_PRESS 02
# define KEY_RELEASE 03
# define DESTROY_NOTIFY 17

/*
** MLX SYNC
*/
# define MLX_SYNC_IMAGE_WRITABLE 1
# define MLX_SYNC_WIN_FLUSH_CMD 2
# define MLX_SYNC_WIN_CMD_COMPLETED 3

/*
** X11 EVENTS MASKS:
** # define NO_EVENT_MASK				0L
** # define KEY_PRESS_MASK				(1L<<0)
** # define KEY_RELEASE_MAS				(1L<<1)
*/

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	esc;
	int	scroll_in;
	int	scroll_out;
	int	plus;
	int	minus;
}	t_keys;

typedef struct s_julia
{
	double			c_re;
	double			c_im;		 	 //real and imaginary part of the constant c
	double			new_re;
	double			new_im;
	double			old_re;
	double			old_im;	 	 //real and imaginary parts of new and old z
	double			zoom;
	double			move_x;
	double			move_y;		//you can change these to zoom and change position
	unsigned int	color;	 	 //the RGB color value for the pixel
	int				max_iterations;  //after how much iterations the function should stop
	/* double			time;
	double			old_time; */
	double			frame_time; //current and old time, and their difference (for input)
}	t_julia;

typedef struct s_mandelbrot
{
	double			pr;
	double			pi;		 	 //real and imaginary part of the pixel p
	double			new_re;
	double			new_im;
	double			old_re;
	double			old_im;	 	 //real and imaginary parts of new and old z
	double			zoom;
	double			move_x;
	double			move_y;		//you can change these to zoom and change position
	unsigned int	color;	 	 //the RGB color value for the pixel
	int				max_iterations;  //after how much iterations the function should stop
	/* double			time;
	double			old_time; */
	double			frame_time; //current and old time, and their difference (for input)
}	t_mandelbrot;

typedef struct s_fractol
{
	int				is_mandelbrot;
	int				is_julia;
	void			*mlx;
	void			*window;
	t_mandelbrot	mandel;
	t_julia			julia;
	int				eje_x;
	int				eje_y;
	t_keys			key;
	t_data			img;
}	t_fractol;

void	print_error(char *str);
int		keys_press(int tecla, t_fractol *fractol);
int		keys_release(int tecla, t_fractol *fractol);
int		scroll_mouse(int tecla, int x, int y, t_fractol *fractol);
int		destroy();
int		mandelbrot(t_fractol *fractol);
int		julia(t_fractol *fractol);
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_data *data, int x, int y, unsigned int color);

#endif