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

# define WIDTH 1280
# define HEIGHT 720

# define EPSILON 1e-5

# define SYNTAX "wrong scene syntax"
# define MALLOC "malloc rip"
# define BYE "bye, have a great time\n"
# define RT "need *.rt file only"
# define FILE_ERR "can not open file"
# define ERROR "ERROR!"

# define SYNTAX_ERROR 228
# define MALLOC_ERROR 11
# define GAY 88
# define CUM 14
# define SEX 13
# define ERROR_CODE 15

# define SPHERE_TYPE 1
# define PLANE_TYPE 2
# define CYLINDER_TYPE 3
# define CONE_TYPE 4

# define T_MIN 0
# define T_MAX DBL_MAX

# define ONLY_FREE -228

# define START_RECURSION -2

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}t_env;

typedef struct s_rgb
{
	double 				r;
	double 				g;
	double 				b;
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


typedef struct	s_ray
{
	t_dot		origin;
	t_dot		direction;
}				t_ray;

typedef struct	s_inter_point
{
	double		t;
	double		t1;
	double		t2;
	t_dot		coord;
	t_dot		normal;
	int			hit;
	double		pixel_intensity;
	int			color;
	int			id;
	int			type;
	t_ray		ray;
}				t_inter_point;

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
//	double				oc;					//вектор от камеры до центра сферы, чтобы не пересчитывать каждый раз
	t_rgb				rgb;
	t_dot				orientation_vec;	//for plane&cylinder only
	double				radius;
	// double				rr;			//радиус сферы в квадрате, чтобы его не пересчитывать каждый раз
	double				height;
	char				refl;
	double				dist1;
	double				dist2;
	t_dot				normal;
	struct s_figure		*next;
}t_figure;

typedef struct s_intersec
{
	t_figure			*closest_f;
	double				closest_t;
	double				t_min;
}t_intersec;

typedef	struct s_elem
{
	t_dot	cross;
}t_elem;


typedef struct s_parametrs
{
	t_dot				point;
	t_dot				normal;
	t_dot				multed;
	t_dot				view;
}t_parametrs;

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
	t_dot				*ray;
	t_parametrs			params;
}t_inf;

t_dot		reflect_ray(t_dot *v1, t_dot *v2);
double   	dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b);
double		cyl_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b);
double		cone_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b, double tan);
void		normalize_vector(t_dot *vector);
double		vector_length(t_dot *vector);
int			create_trgb(int t, int r, int g, int b);
t_dot		subtraction_vector(t_dot *vector_a, t_dot *vector_b);
void		my_mlx_pixel_put(t_inf *data, int x, int y, int color);
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
t_rgb		change_color_intensity(t_rgb *color, double intense);
double		compute_lightning(t_dot vec_l, t_inf *inf, double spec);
t_dot		multiply_vector(t_dot *vector, double num);
t_dot		addition_vector(t_dot *vector_a, t_dot *vector_b);
void		closest_intersection(t_dot *origin, t_inf *inf, t_intersec *cls);
t_rgb		addition_rgb(t_rgb col1, t_rgb col2);
t_dot		reflect_ray(t_dot *v1, t_dot *v2);
void		get_color(t_dot *origin, t_rgb *rgb, char depth, t_inf *inf);
t_rgb		addition_rgb(t_rgb col1, t_rgb col2);
t_dot		reflect_ray(t_dot *v1, t_dot *v2);
void		ray_tracing(t_inf *inf, int mlx_y, int mlx_x, double y);
char		is_intersect(t_intersec *cls, t_inf *inf, t_dot *origin, double flag);
void		closest_sphere(t_dot *origin, t_figure *figure, t_inf *inf, t_intersec *cls);
// double		intersect_ray_cylinder(t_dot *o, t_dot *d, t_figure *cyl);
double		intersect_ray_plane(t_dot *o, t_dot *ray, t_dot *coordinates, t_dot *orientation_vec);
double		cyl_and_cap_inter(t_dot o, t_dot *d, t_figure *cyl);
double		distance(t_dot p1, t_dot p2);
t_dot		vec_cross(t_dot *vector_a, t_dot *vector_b);
t_dot		vec_add(t_dot vector_a, t_dot vector_b);
t_dot		sub(t_dot a, t_dot b);
double		dot(t_dot a, t_dot b);
t_dot		normalize(t_dot a);
t_dot		add(t_dot a, t_dot b);
t_dot		ft_scale(t_dot a, double b);
void		ft_get_normal(t_ray ray, t_dot obj_pos,
		t_inter_point *inter_point);
double		get_norm(t_dot vect);
double		min(double a, double b);


t_rgb	change_color_light(t_inf *inf, t_rgb *start_rgb);

# endif
