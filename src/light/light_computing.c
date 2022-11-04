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

t_rgb	change_color_light(t_inf *inf, t_rgb *start_rgb)
{
	t_rgb	with_light;

	with_light.r = start_rgb->r + inf->amb.rgb.r;
	with_light.g = start_rgb->g + inf->amb.rgb.g;
	with_light.b = start_rgb->b + inf->amb.rgb.b;
	return (with_light);
}

t_rgb	change_color_intensity(t_rgb *color, double intense)
{
	t_rgb	rgb;

	rgb.r = color->r * intense;
	rgb.g = color->g * intense;
	rgb.b = color->b * intense;
	return (rgb);
}

double	compute_lightning(t_dot vec_l, t_inf *inf, double spec,
		t_parametrs *params)
{
	t_intersec	cls;
	t_dot		vec_r;
	double		n_dot_l;
	double		r_dot_v;
	double		intense;

	intense = inf->amb.ratio;
	inf->ray = &vec_l;
	closest_intersection(&params->point, inf, &cls);
	if (is_intersect(&cls, inf, &params->point, 0))
		return (intense);
	n_dot_l = dot_product_of_vectors(&params->normal, &vec_l);
	if (n_dot_l > 0)
		intense += inf->light.brightness * n_dot_l
			/ (vector_length(&params->normal) * vector_length(&vec_l));
	if (spec != -1)
	{
		vec_r = reflect_ray(&vec_l, &params->normal);
		r_dot_v = dot_product_of_vectors(&vec_r, &params->view);
		if (r_dot_v > 0)
			intense += inf->light.brightness * pow(r_dot_v
					/ (vector_length(&vec_r)
						* vector_length(&params->view)), spec);
	}
	return (intense);
}
