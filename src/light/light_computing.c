#include "minirt.h"

t_rgb	change_color_intensity(t_rgb *color, double intense)
{
	t_rgb	rgb;

	rgb.r = color->r * intense;
	rgb.g = color->g * intense;
	rgb.b = color->b * intense;
	return (rgb);
}

double	compute_lightning(t_dot *point, t_dot *normal, t_dot *view, t_inf *inf, double spec)
{
	t_intersec	cls;
	t_dot		vec_l;
	t_dot		vec_r;
	double		n_dot_l;
	double		r_dot_v;
	double		intense;

	intense = inf->amb.ratio;
	vec_l = subtraction_vector(&inf->light.l_point, point);
	inf->ray = &vec_l;
	cls.t_min = 1e-2;
	cls.closest_t = 1.0;
	cls.closest_f = NULL;
	closest_intersection(point, inf, &cls);
	if (cls.closest_f)
		return (intense);
	n_dot_l = dot_product_of_vectors(normal, &vec_l);
	if (n_dot_l > 0)
		intense += + inf->light.brightness * n_dot_l /
				(vector_length(normal) * vector_length(&vec_l));
	//spec. reflection
	if (spec != -1)
	{
		vec_r = reflect_ray(&vec_l, normal);
		r_dot_v = dot_product_of_vectors(&vec_r, view);
		if (r_dot_v > 0)
			intense += inf->light.brightness * pow(r_dot_v / (vector_length(&vec_r) * vector_length(view)), spec);
	}
	return (intense);
}