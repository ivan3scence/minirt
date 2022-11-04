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

#include "minirt.h"

static void	closest_figure(t_dot *origin, t_figure *figure, t_inf *inf,
		t_intersec *cls)
{
	double	tt;

	if (figure->type == SPHERE_TYPE)
		tt = intersect_ray_sphere(subtraction_vector(origin,
					&figure->coordinates), inf->ray, figure);
	else if (figure->type == CYLINDER_TYPE)
		tt = cyl_and_cap_inter(subtraction_vector(origin,
					&figure->coordinates), inf->ray, figure);
	// else if (figure->type == CONE_TYPE)
	// 	tt = intersect_ray_cone(subtraction_vector(origin,
	// 				&figure->coordinates), inf->ray, figure, inf);
	else if (figure->type == PLANE_TYPE)
		tt = intersect_ray_plane(&inf->cam.view_point, inf->ray,
				&figure->coordinates, &figure->orientation_vec);
	else
		return ;
	if (tt > cls->t_min && tt < cls->closest_t)
	{
		cls->closest_t = tt;
		cls->closest_f = figure;
	}
}

void	closest_intersection(t_dot *origin, t_inf *inf, t_intersec *cls)
{
	t_figure	*figure;

	figure = inf->figures;
	while (figure)
	{
		closest_figure(origin, figure, inf, cls);
		figure = figure->next;
	}
}

static void	background(t_rgb *rgb)
{
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
}

char	is_intersect(t_intersec *cls, t_inf *inf, t_dot *origin, double flag)
{
	cls->t_min = (double)flag * 1e-10 + (!flag) * 1e-2;
	cls->closest_t = (double)flag * DBL_MAX + (!flag) * 1.0;
	cls->closest_f = NULL;
	closest_intersection(origin, inf, cls);
	if (cls->closest_f)
		return (1);
	return (0);
}

void	get_color(t_dot *origin, t_rgb *rgb, char depth, t_inf *inf)
{
	t_parametrs	params;

	if (!is_intersect(&params.cls, inf, origin, 1))
		return (background(rgb));
	*rgb = params.cls.closest_f->rgb;
	params.multed = multiply_vector(inf->ray, params.cls.closest_t);
	params.point = addition_vector(origin, &params.multed);
	params.normal = subtraction_vector(&params.point,
			&params.cls.closest_f->coordinates);
	params.normal = multiply_vector(&params.normal, 1.0
			/ vector_length(&params.normal));
	params.view = multiply_vector(inf->ray, -1);
	params.tmp_light = change_color_light(inf, rgb);
	params.color_without_reflection = change_color_intensity(&params.tmp_light,
			compute_lightning(subtraction_vector(&inf->light.l_point,
					&params.normal), inf, 100, &params));
	if (depth == START_RECURSION)
	{
		depth = params.cls.closest_f->refl;
	}
	if (depth > 0)
		reflection(rgb, &params, inf, --depth);
	else
		*rgb = params.color_without_reflection;
}
