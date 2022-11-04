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

void	normalize_vector(t_dot *vector)
{
	double	norm;
	double	length;

	length = vector_length(vector);
	norm = 1 / length;
	vector->x = vector->x * norm;
	vector->y = vector->y * norm;
	vector->z = vector->z * norm;
}

double	dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b)
{
	double	res;

	res = ((vector_a->x * vector_b->x) + (vector_a->y * vector_b->y)
			+ (vector_a->z * vector_b->z));
	return (res);
}

double	cyl_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b)
{
	return ((vector_a->x * vector_b->x) + (vector_a->z * vector_b->z));
}

// double	cone_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b,
// 		double tan)
// {
// 	return (vector_a->x * vector_b->x + vector_a->z * vector_b->z
// 		- tan * vector_a->y * vector_b->y);
// }

t_dot	multiply_vector(t_dot *vector, double num)
{
	t_dot	multed;

	multed.x = vector->x * num;
	multed.y = vector->y * num;
	multed.z = vector->z * num;
	return (multed);
}
