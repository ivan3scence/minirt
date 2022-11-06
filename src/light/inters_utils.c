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

double	intersect_ray_cone(t_dot *o, t_dot *d, t_figure *cone)
{
	t_inter_point	inter_point;
	t_ri_cyl		ri;
	double			tan;

	tan = cone->radius * cone->radius / cone->height / cone->height;
	normalize_vector(&cone->orientation_vec);
	ri.cross = *d;
	ri.c_to_o = subtraction_vector(o, &cone->coordinates);
	ri.cross2 = *o;
	ri.sub = subtraction_vector(o, &cone->coordinates);
	ri.a = cone_dot_product_of_vectors(&ri.cross, &ri.cross, tan);
	ri.b = 2 * cone_dot_product_of_vectors(&ri.cross, &ri.cross2, tan);
	ri.c = cone_dot_product_of_vectors(&ri.cross2, &ri.cross2, tan);
	ri.delta = ri.b * ri.b - 4 * ri.c * ri.a;
	if (ri.delta < EPSILON)
		return (DBL_MAX);
	inter_point.t1 = (-ri.b - sqrt(ri.delta)) / (2 * ri.a);
	inter_point.t2 = (-ri.b + sqrt(ri.delta)) / (2 * ri.a);
	if (inter_point.t2 < 0 && inter_point.t1 < 0)
		return (DBL_MAX);
	inter_point.t = inter_point.t1;
	if (inter_point.t2 < inter_point.t1)
		inter_point.t = inter_point.t2;
	return (inter_point.t);
}

double	cone_and_cap_inter(t_dot o, t_dot *d, t_figure *cyl)
{
	double	cone_iner;

	cone_iner = intersect_ray_cone(&o, d, cyl);
	return (cone_iner);
}
