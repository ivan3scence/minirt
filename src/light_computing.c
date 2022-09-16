#include "minirt.h"

t_rgb	*change_color_intensity(t_rgb *color, double intense)
{
	color->r *= intense;
	color->g *= intense;
	color->b *= intense;
	return (color);
}

double	compute_lightning(t_dot *point, t_dot *normal, t_dot *view, t_inf *inf, int spec)
{
	t_dot	vec_l;
	t_dot	vec_r;
	double	n_dot_l;
	double	r_dot_v;

	vec_l = subtraction_vector(&inf->light.l_point, point);
	n_dot_l = dot_product_of_vectors(normal, &vec_l);
	if (n_dot_l > 0)
		n_dot_l = inf->amb.ratio + inf->light.brightness * n_dot_l /
				(vector_length(normal) * vector_length(&vec_l));
	//spec. reflection
	if (spec != -1)
	{
		t_dot mult=multiply_vector(normal, 2.0 * dot_product_of_vectors(normal, &vec_l));
		vec_r = subtraction_vector(&mult, &vec_l);
		r_dot_v = dot_product_of_vectors(&vec_r, view);
		if (r_dot_v > 0)
			n_dot_l += inf->light.brightness * pow(r_dot_v / (vector_length(&vec_r) * vector_length(view)), spec);
	}
//	printf("%g\n", n_dot_l);
	return (n_dot_l);
}