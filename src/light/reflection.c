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

t_rgb	addition_rgb(t_rgb col1, t_rgb col2)
{
	t_rgb	added;

	added.r = col1.r + col2.r;
	added.g = col1.g + col2.g;
	added.b = col1.b + col2.b;
	return (added);
}

t_dot	reflect_ray(t_dot *v1, t_dot *v2)
{
	t_dot	new;
	t_dot	mult;

	mult = multiply_vector(v2, 2 * dot_product_of_vectors(v1, v2));
	new = subtraction_vector(&mult, v1);
	return (new);
}

void	reflection(t_rgb *rgb, t_parametrs *params,
		t_inf *inf, char depth)
{
	t_dot		refl_ray;

	if (!depth)
	{
		*rgb = params->color_without_reflection;
		return ;
	}
	refl_ray = reflect_ray(&params->view, &params->normal);
	inf->ray = &refl_ray;
	get_color(&params->point, rgb, --depth, inf);
	*rgb = addition_rgb(change_color_intensity(
				&params->color_without_reflection, 1 - 0.5),
			change_color_intensity(rgb, 0.5));
}
