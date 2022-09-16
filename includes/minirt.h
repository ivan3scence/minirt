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
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# include "libft.h"
# include "mlx.h"
# include "get_next_line_bonus.h"

# define WIDTH 1920
# define HEIGHT 1080
# define SYNTAX "wrong scene syntax"
# define MALLOC "malloc rip"
# define BYE "bye, have a great time"
# define SYNTAX_ERROR 228
# define MALLOC_ERROR 11
# define GAY 88
# define CUM 14
# define SPHERE_TYPE 1
# define PLANE_TYPE 2
# define CYLINDER_TYPE 3
# define T_MIN -5
# define T_MAX DBL_MAX
# define ONLY_FREE -228

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}t_env;

typedef struct s_rgb
{
	int 				r;
	int 				g;
	int 				b;
}t_rgb;

typedef struct s_dot
{
	double				x;
	double				y;
	double				z;
}t_dot;

typedef struct s_vplane
{
	float				width;
	float				height;
	float				ratio;
	float				x_pixel;
	float				y_pixel;
	unsigned char		fov;
}t_vplane;

typedef struct s_ambient
{
	t_rgb				rgb;
	double				ratio;
}t_ambient;

typedef struct s_camera
{
	t_dot				view_point;
	t_dot				n_vector;
	unsigned char		fov;
}t_camera;

typedef struct s_light
{
	t_dot				l_point;
	double				brightness;
	t_rgb				rgb;
}t_light;

typedef struct s_figure
{
	char				type;				//1 - sphere;2 - plane; 3 - cylinder;
	t_dot				coordinates;
	t_rgb				rgb;
	t_dot				orientation_vec;	//for plane&cylinder only
	double				sphere_radius;
	double				cylinder_diametr;
	double				cylinder_height;
	struct s_figure		*next;
}t_figure;

typedef struct s_intersec
{
	t_figure	*closest_f;
	double		closest_t;
}				t_intersec;

typedef struct s_inf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	t_ambient			amb;
	t_camera			cam;
	t_light				light;
	t_figure			*figures;
}t_inf;

double   	dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b);
void		normalize_vector(t_dot *vector);
double		vector_length(t_dot *vector);
int			create_trgb(int t, int r, int g, int b);
t_dot		subtraction_vector(t_dot *vector_a, t_dot *vector_b);
void		my_mlx_pixel_put(t_inf *data, int x, int y, int color);
void 		ray_tracing(t_inf *inf);
t_rgb 		new_rgb(unsigned char x, unsigned char y, unsigned char z);
t_dot 		new_dot(double x, double y, double z);
t_inf		*parse(char *filename);
double		ft_dbatoi(char *str);
int			ft_arrlen(char **split);
void		ft_clean_split(char **split);
t_rgb		set_rgb(t_inf *inf, char *str);
t_dot		set_coordinates(t_inf *inf, char *str);
t_figure	*ft_last_figure(t_figure *fig);
void 		free_exit(char *desc, t_inf *inf, int exit_code);
void		*free_split(char **split);
t_rgb		*change_color_intensity(t_rgb *color, double intense);
double		compute_lightning(t_dot *point, t_dot *normal, t_dot *view, t_inf *inf, int spec);
t_dot		multiply_vector(t_dot *vector, double num);
t_dot		addition_vector(t_dot *vector_a, t_dot *vector_b);

# endif
