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

t_dot	vec_cross(t_dot *vector_a, t_dot *vector_b)
{
	t_dot	v;

	v.x = vector_a->y * vector_b->z - vector_a->z * vector_b->y;
	v.y = vector_a->z * vector_b->x - vector_a->x * vector_b->z;
	v.z = vector_a->x * vector_b->y - vector_a->y * vector_b->x;
	return (v);
}

double	get_norm(t_dot vect)
{
	return (sqrt(dot(vect, vect)));
}

t_dot	ft_scale(t_dot a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return (a);
}

t_dot	add(t_dot a, t_dot b)
{
	t_dot	vect;

	vect.x = a.x + b.x;
	vect.y = a.y + b.y;
	vect.z = a.z + b.z;
	return (vect);
}

t_dot	normalize(t_dot a)
{
	t_dot	vect;
	double	len;

	len = get_norm(a);
	vect.x = a.x / len;
	vect.y = a.y / len;
	vect.z = a.z / len;
	return (vect);
}
