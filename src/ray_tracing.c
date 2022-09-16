#include "minirt.h"

t_vplane	get_view_plane(double width, double height, unsigned char fov)
{
	t_vplane	vplane;

	vplane.width = 2 * tan(fov / 2 * M_PI / 180);
	vplane.fov = fov;
	vplane.ratio = width / height;
	vplane.height = vplane.width / vplane.ratio;
	vplane.x_pixel = vplane.width / width;
	vplane.y_pixel = vplane.height / height;
	return (vplane);
}


double	*intersect_ray_sphere(t_dot cam_sphere, t_dot *ray, t_figure *sphere, t_inf *inf)
{
	double	b;
	double	c;
	double	disc;
	double	*tt;

	tt = (double *)malloc(sizeof(double) * 2);
	if (!tt)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	b = 2 * dot_product_of_vectors(&cam_sphere, ray);
	c = dot_product_of_vectors(&cam_sphere, &cam_sphere) - sphere->sphere_radius * sphere->sphere_radius;
	disc = b * b - 4 * c;
	if (disc < 0)
		return (tt);
	tt[0] = (-b - sqrt(disc)) / 2;
	tt[1] = (-b + sqrt(disc)) / 2;
	return (tt);
}

t_intersec	closest_intersection(t_dot *ray, t_inf *inf, t_figure *figure)
{
	t_intersec	cls;
	double		*tt;

	cls.closest_f = NULL;
	cls.closest_t = DBL_MAX;
	while (figure)
	{
		if (figure->type == SPHERE_TYPE)
		{
			tt = intersect_ray_sphere(subtraction_vector(&inf->cam.view_point, &figure->coordinates), ray, figure, inf);
			if (tt[0] >= T_MIN && tt[0] <= T_MAX && tt[0] < cls.closest_t) {
				cls.closest_t = tt[0];
				cls.closest_f = figure;
			}
			if (tt[1] >= T_MIN && tt[1] <= T_MAX && tt[1] < cls.closest_t) {
				cls.closest_t = tt[1];
				cls.closest_f = figure;
			}
			free(tt);
		}
		figure = figure->next;
	}
	return (cls);
}

t_rgb	*get_color(t_inf *inf, t_dot *ray, t_rgb *rgb)
{
	t_intersec	cls;
	t_dot		point;
	t_dot		normal;

	cls = closest_intersection(ray, inf, inf->figures);
	if (!cls.closest_f)
	{
		rgb->r = 0;
		rgb->g = 0;
		rgb->b = 0;
		return (rgb);
	}
	rgb->r = cls.closest_f->rgb.r;
	rgb->g = cls.closest_f->rgb.g;
	rgb->b = cls.closest_f->rgb.b;
	multiply_vector(ray, cls.closest_t);									//!!!!!!!!!!!!
	point = addition_vector(&inf->cam.view_point, ray);
	normal = subtraction_vector(&point, &cls.closest_f->coordinates);
	return (change_color_intensity(rgb, compute_lightning(&point, &normal, inf)));
}

void 	ray_tracing(t_inf *inf)
{
	int 		mlx_x;
	int 		mlx_y;
	double		x;
	double		y;
	double		x_ray;
	double		y_ray;
	t_vplane	vplane;
	t_dot		ray;
	t_rgb		color;

	mlx_y = 0;
	y = HEIGHT / 2;
	vplane = get_view_plane(WIDTH, HEIGHT, inf->cam.fov);
	while (y > -HEIGHT / 2)
	{
		y_ray = y * vplane.y_pixel;
		x = -WIDTH / 2;
		mlx_x = -1;
		while (x < WIDTH / 2)
		{
			x_ray = x * vplane.x_pixel;
			ray = new_dot(x_ray, y_ray, -1);
			normalize_vector(&ray);
			get_color(inf, &ray, &color);
			my_mlx_pixel_put(inf, ++mlx_x, mlx_y, create_trgb(0, color.r, color.g, color.b));
			++x;
		}
		++mlx_y;
		--y;
	}
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
}