/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# include "libft.h"
# include "mlx.h"

# define WIDTH 1920
# define HEIGHT 1080
# define CAMERA_ROTATION 1
# define CANVAS_HEIGHT 1
# define CANVAS_WIDTH 1
# define CANVAS_Z 0.5

typedef struct s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}				t_rgb;

typedef struct s_dot
{
	double		x;
	double		y;
	double		z;
}				t_dot;

typedef struct s_sphere
{
	t_dot		center;
	double		radius;
	t_rgb		color;
}				t_sphere;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	t_sphere	**spheres;
}				t_mlx;

typedef struct s_intersec
{
	t_sphere	*closest_sphere;
	double		closest_t;
}				t_intersec;

# endif
