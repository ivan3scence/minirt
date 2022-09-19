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
