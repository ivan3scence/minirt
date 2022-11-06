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

double	intersect_ray_plane(t_dot o, t_dot *ray, t_dot *coordinates,
			t_dot *orientation_vec)
{
	double	numerator;
	double	denominator;
	double	sol;
	double	tt;

	tt = INT_MAX;
	(void)coordinates;
	denominator = dot_product_of_vectors(ray, orientation_vec);
	if (fabs(denominator) < EPSILON)
		return (tt);
	numerator = dot_product_of_vectors(&o, orientation_vec);
	sol = numerator / denominator;
	if (sol < EPSILON || DBL_MAX <= sol)
		return (tt);
	tt = sol;
	return (tt);
}

double	intersect_ray_sphere(t_dot cam_sphere, t_dot *ray, t_figure *sphere)
{
	double	b;
	double	c;
	double	a;
	double	disc;
	double	tt[2];

	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	a = dot_product_of_vectors(ray, ray);
	b = 2 * dot_product_of_vectors(&cam_sphere, ray);
	c = dot_product_of_vectors(&cam_sphere, &cam_sphere)
		- sphere->radius * sphere->radius;
	disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (DBL_MAX);
	tt[0] = (-b - sqrt(disc)) / (2 * a);
	tt[1] = (-b + sqrt(disc)) / (2 * a);
	if (tt[0] <= tt[1])
		return (tt[0]);
	return (tt[1]);
}

double	cone_cap_intersection(t_dot *o, t_dot *d, t_figure *cyl,
		t_dot (*func)(t_dot*, t_dot*))
{
	double	id1;
	double	lol;
	t_dot	ip1;
	t_dot	c1;
	t_dot	mult;

	ip1 = multiply_vector(&cyl->orientation_vec, cyl->height / 2.0);
	c1 = (*func)(&cyl->coordinates, &ip1);
	id1 = intersect_ray_plane(*o, d, &c1, &cyl->orientation_vec);
	if (id1 < DBL_MAX)
	{
		mult = multiply_vector(d, id1);
		ip1 = addition_vector(o, &mult);
		ip1 = subtraction_vector(&ip1, &c1);
		lol = dot_product_of_vectors(&ip1, &ip1);
		if (sqrt(lol) <= cyl->radius)
			return (id1);
	}
	return (DBL_MAX);
}

static double	cone_capsssex(t_figure *cyl, t_dot *d,
			t_inter_point inter_point, t_dot *o)
{
	double	a;
	double	max;
	t_ray	ray;

	ray.origin = *o;
	ray.direction = *d;
	ft_get_normal(ray, cyl->coordinates, &inter_point);
	max = sqrt(pow(cyl->height / 2.0, 2) + pow(cyl->radius, 2));
	if (get_norm(sub(inter_point.coord, cyl->coordinates)) > max)
	{
		inter_point.t = (inter_point.t2);
		ft_get_normal(ray, cyl->coordinates, &inter_point);
	}
	if (get_norm(sub(inter_point.coord, cyl->coordinates)) > max)
		return (DBL_MAX);
	a = dot(cyl->orientation_vec, sub(inter_point.coord, cyl->coordinates));
	inter_point.normal = normalize(sub(inter_point.coord, add(cyl->coordinates,
					ft_scale(cyl->orientation_vec, a))));
	a = dot(ray.direction, inter_point.normal);
	if (a > 0)
		inter_point.normal = ft_scale(inter_point.normal, -1);
	return (inter_point.t);
}

// double	intersect_ray_cone(t_dot *o, t_dot *d, t_figure *cone)
// {
// 	t_inter_point	inter_point;
// 	t_ri_cyl		ri;
// 	double			tan;

// 	tan = cone->radius * cone->radius / cone->height / cone->height;
// 	normalize_vector(&cone->orientation_vec);
// 	ri.cross = *d;
// 	ri.c_to_o = subtraction_vector(o, &cone->coordinates);
// 	ri.cross2 = *o;
// 	ri.sub = subtraction_vector(o, &cone->coordinates);
// 	ri.a = cone_dot_product_of_vectors(&ri.cross, &ri.cross, tan);
// 	ri.b = 2 * cone_dot_product_of_vectors(&ri.cross, &ri.cross2, tan);
// 	ri.c = cone_dot_product_of_vectors(&ri.cross2, &ri.cross2, tan);
// 	ri.delta = ri.b * ri.b - 4 * ri.c * ri.a;
// 	if (ri.delta < EPSILON)
// 		return (DBL_MAX);
// 	inter_point.t1 = (-ri.b - sqrt(ri.delta)) / (2 * ri.a);
// 	inter_point.t2 = (-ri.b + sqrt(ri.delta)) / (2 * ri.a);
// 	if (inter_point.t2 < 0 && inter_point.t1 < 0)
// 		return (DBL_MAX);
// 	inter_point.t = inter_point.t1;
// 	if (inter_point.t2 < inter_point.t1)
// 		inter_point.t = inter_point.t2;
// 	return (inter_point.t);
// 	return (cone_capsssex(cone, d, inter_point, o));
// }

// double	cone_and_cap_inter(t_dot o, t_dot *d, t_figure *cyl)
// {
// 	double	cone_iner;

// 	cone_iner = intersect_ray_cone(&o, d, cyl);
// 	return (cone_iner);
// }
