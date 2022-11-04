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

t_dot	vec_add(t_dot vector_a, t_dot vector_b)
{
	t_dot	v;

	v.x = vector_a.x + vector_b.x;
	v.y = vector_a.y + vector_b.y;
	v.z = vector_a.z + vector_b.z;
	return (v);
}

double	distance(t_dot p1, t_dot p2)
{
	double	d;

	d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	return (d);
}

void	ft_get_normal(t_ray ray, t_dot obj_pos,
		t_inter_point *inter_point)
{
	ray.direction.x *= inter_point->t;
	ray.direction.y *= inter_point->t;
	ray.direction.z *= inter_point->t;
	inter_point->coord = addition_vector(&ray.origin, &ray.direction);
	inter_point->normal = subtraction_vector(&inter_point->coord, &obj_pos);
	normalize_vector(&inter_point->normal);
}

t_dot	sub(t_dot a, t_dot b)
{
	t_dot	vect;

	vect.x = a.x - b.x;
	vect.y = a.y - b.y;
	vect.z = a.z - b.z;
	return (vect);
}

double	dot(t_dot a, t_dot b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
