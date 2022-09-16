#include "minirt.h"

t_rgb	*change_color_intensity(t_rgb *color, double intense)
{
	color->r *= intense;
	color->g *= intense;
	color->b *= intense;
	return (color);
}

double	compute_lightning(t_dot *point, t_dot *normal, t_inf *inf)
{
	t_dot	vec_l;
	double	prod;

	vec_l = subtraction_vector(&inf->light.l_point, point);
	prod = dot_product_of_vectors(normal, &vec_l);
	if (prod > 0)
		prod = inf->amb.ratio + inf->light.brightness * prod /
				(vector_length(normal) * vector_length(&vec_l));
	return (prod);
}