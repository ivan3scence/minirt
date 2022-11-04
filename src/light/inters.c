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

double	intersect_ray_plane(t_dot *o, t_dot *ray, t_dot *coordinates,
		t_dot *orientation_vec)
{
	t_dot	hui;
	double	tt;
	double	dist;
	double	denom;
	double	result;

	tt = 0;
	dist = INT_MAX;
	denom = dot_product_of_vectors(orientation_vec, ray);
	hui = subtraction_vector(coordinates, o);
	tt = dot_product_of_vectors(orientation_vec, &hui);
	result = fabs(tt - denom);
	if (result < dist)
		return (result);
	else
		return (dist);
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

// double	intersect_ray_cone(t_dot cam, t_dot *ray,
// 		t_figure *cone, t_inf *inf)
// {
// 	double	b;
// 	double	c;
// 	double	a;
// 	double	disc;
// 	double	tt[2];
// 	double	tan;

// 	(void)*inf;

// 	tt[0] = DBL_MAX;
// 	tt[1] = DBL_MAX;
// 	tan = cone->radius * cone->radius / cone->height / cone->height;
// 	a = cone_dot_product_of_vectors(ray, ray, tan);
// 	b = 2 * cone_dot_product_of_vectors(&cam, ray, tan);
// 	c = cone_dot_product_of_vectors(&cam, &cam, tan);
// 	disc = b * b - 4 * a * c;
// 	if (disc < EPSILON)
// 		return (DBL_MAX);
// 	tt[0] = (-b - sqrt(disc)) / (2 * a);
// 	tt[1] = (-b + sqrt(disc)) / (2 * a);
// 	double y1 = cam.y + tt[0] * ray->y;
// 	double y2 = cam.y + tt[1] * ray->y;
// 	double ymin = cone->coordinates.y - cone->height;
// 	double ymax = cone->coordinates.y;
// 	if (y1 < ymin || y1 > ymax || y2 < ymin || y2 > ymax)
// 	{
// 		tt[0] = DBL_MAX;
// 		tt[1] = DBL_MAX;
// 	}
// 	if ((y1 < y2 && y1 < ymin && y2 > ymin)
		//|| (y1 > y2 && y2 < ymin && y1 > ymin))
// 		tt[0] = (ymin - cam.y) / ray->y;
// 	if (tt[0] <= tt[1])
// 		return (tt[0]);
// 	return (tt[1]);
// }
