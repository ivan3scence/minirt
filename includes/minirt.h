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

# include "libft.h"
# include "mlx.h"
# include "get_next_line_bonus.h"

# define SYNTAX "wrong scene syntax"
# define SYNTAX_CODE 228
# define GAY 88
# define CUM 14

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}t_env;

typedef struct s_rgb
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;
}t_rgb;

typedef struct s_dot
{
	double				x;
	double				y;
	double				z;
}t_dot;

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
	double				sphere_diametr;
	double				cylinder_diametr;
	double				cylinder_height;
	struct s_figure		*next;
}t_figure;

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

t_inf	*parse(char *filename);
double	ft_dbatoi(char *str);
int	ft_arrlen(char **split);
void	ft_clean_split(char **split);
t_rgb	set_rgb(t_inf *inf, char *str);
t_dot	set_coordinates(t_inf *inf, char *str);
t_figure	*ft_last_figure(t_figure *fig);
void 	free_exit(char *desc, t_inf *inf, unsigned char exit_code);

# endif
