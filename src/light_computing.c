#include "minirt.h"

t_rgb	change_color_intensity(t_rgb *color, double intense)
{
	t_rgb	rgb;
//	color->t = 255 - color->t * intense;
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
	cls = closest_intersection(point, &vec_l, inf, inf->figures, 1e-2, 1.0);
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
		{
			intense += inf->light.brightness * pow(r_dot_v / (vector_length(&vec_r) * vector_length(view)), spec);
//			if (intense > 1.5)
//			{
//				intense = 255;
//				printf("%g\n", intense);
//			}
		}
	}
	return (intense);
//	return (1);
}