#include "minirt.h"

t_rgb	change_color_intensity(t_rgb *color, double intense)
{
	t_rgb	rgb;

	rgb.r = color->r * intense;
	rgb.g = color->g * intense;
	rgb.b = color->b * intense;
	return (rgb);
}

double	compute_lightning(t_dot vec_l, t_inf *inf, double spec)
{
	t_intersec	cls;
	t_dot		vec_r;
	double		n_dot_l;
	double		r_dot_v;
	double		intense;

	intense = inf->amb.ratio;
	inf->ray = &vec_l;
	closest_intersection(&inf->params.point, inf, &cls);
	if (is_intersect(&cls, inf, &inf->params.point, 0))
		return (intense);
	n_dot_l = dot_product_of_vectors(&inf->params.normal, &vec_l);
	if (n_dot_l > 0)
		intense += inf->light.brightness * n_dot_l
			/ (vector_length(&inf->params.normal) * vector_length(&vec_l));
	if (spec != -1)
	{
		vec_r = reflect_ray(&vec_l, &inf->params.normal);
		r_dot_v = dot_product_of_vectors(&vec_r, &inf->params.view);
		if (r_dot_v > 0)
			intense += inf->light.brightness * pow(r_dot_v
					/ (vector_length(&vec_r)
						* vector_length(&inf->params.view)), spec);
	}
	return (intense);
}
