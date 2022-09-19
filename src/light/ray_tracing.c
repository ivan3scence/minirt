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

//double	*intersect_ray_cylinder(t_dot cam_cyl, t_dot *ray,
//t_figure *cyl, t_inf *inf)
//{
//	double a = (dir.x * dir.x) + (dir.z * dir.z);
//	double b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
//	double c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
//
//	double delta = b*b - 4*(a*c);
//	if(fabs(delta) < 0.001) return -1.0;
//	if(delta < 0.0) return -1.0;
//
//	double t1 = (-b - sqrt(delta))/(2*a);
//	double t2 = (-b + sqrt(delta))/(2*a);
//	else return ;
//
//	double	b;
//	double	c;
//	double	a;
//	double	disc;
//	double	*tt;
//
//	tt = (double *)malloc(sizeof(double) * 2);
//	if (!tt)
//		free_exit(MALLOC, inf, MALLOC_ERROR);
//	a = ray->x * ray->x + ray->z * ray->z;
//	b = 2 * (ray)
//}

double	*intersect_ray_sphere(t_dot cam_sphere, t_dot *ray, t_figure *sphere, t_inf *inf)
{
	double	b;
	double	c;
	double	a;
	double	disc;
	double	*tt;

	tt = (double *)malloc(sizeof(double) * 2);
	if (!tt)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	a = dot_product_of_vectors(ray, ray);
	b = 2 * dot_product_of_vectors(&cam_sphere, ray);
	c = dot_product_of_vectors(&cam_sphere, &cam_sphere)
		- sphere->sphere_radius * sphere->sphere_radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (tt);
	tt[0] = (-b - sqrt(disc)) / (2 * a);
	tt[1] = (-b + sqrt(disc)) / (2 * a);
	return (tt);
}

void	closest_sphere(t_dot *origin, t_figure *figure, t_inf *inf, t_intersec *cls)
{
	double	*tt;

	tt = intersect_ray_sphere(subtraction_vector(origin,
				&figure->coordinates), inf->ray, figure, inf);
	if (tt[0] > cls->t_min && tt[0] < cls->closest_t)
	{
		cls->closest_t = tt[0];
		cls->closest_f = figure;
	}
	if (tt[1] > cls->t_min && tt[1] < cls->closest_t)
	{
		cls->closest_t = tt[1];
		cls->closest_f = figure;
	}
	free(tt);
}

void	closest_intersection(t_dot *origin, t_inf *inf, t_intersec *cls)
{
	double		*tt;
	t_figure	*figure;

	figure = inf->figures;
	while (figure)
	{
		if (figure->type == SPHERE_TYPE)
			closest_sphere(origin, figure, inf, cls);
		figure = figure->next;
	}
}

void	background(t_rgb *rgb)
{
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
}

// t_dot	get_refl_ray(t_rgb *rgb, t_inf *inf, t_rgb *color_without_reflection, t_intersec *cls, t_dot *origin)
// {
// 	t_dot	view;
// 	t_dot	multed;
// 	t_dot	point;
// 	t_dot	normal;
// 	t_dot	refl_ray;

// 	multed = multiply_vector(inf->ray, cls->closest_t);
// 	point = addition_vector(origin, &multed);
// 	normal = subtraction_vector(&point, &cls->closest_f->coordinates);
// 	normal = multiply_vector(&normal, 1.0 / vector_length(&normal));
// 	view = multiply_vector(inf->ray, -1);
// 	*color_without_reflection = change_color_intensity(rgb, compute_lightning(&point, &normal, &view, inf, 100));
// 	return (reflect_ray(&view, &normal));
// }

char	is_intersect(t_intersec *cls, t_inf *inf, t_dot *origin)
{
	cls->t_min = 1e-10;
	cls->closest_t = DBL_MAX;
	cls->closest_f = NULL;
	closest_intersection(origin, inf, cls);
	if (cls->closest_f)
		return (1);
	return (0);
}

void	reflection(t_rgb *rgb, t_rgb *color_without_reflection,
t_inf *inf, char depth)
{
	t_dot		refl_ray;

	if (!depth)
	{
		*rgb = *color_without_reflection;
		return ;
	}
	refl_ray = reflect_ray(&inf->params.view, &inf->params.normal);
	inf->ray = &refl_ray;
	get_color(&inf->params.point, rgb, --depth, inf);
	*rgb = addition_rgb(change_color_intensity(
				color_without_reflection, 1 - 0.5),
			change_color_intensity(rgb, 0.5));
}

void	get_color(t_dot *origin, t_rgb *rgb, char depth, t_inf *inf)
{
	t_intersec	cls;
	t_rgb		color_without_reflection;

	if (!is_intersect(&cls, inf, origin))
		return (background(rgb));
	*rgb = cls.closest_f->rgb;
	inf->params.multed = multiply_vector(inf->ray, cls.closest_t);
	inf->params.point = addition_vector(origin, &inf->params.multed);
	inf->params.normal = subtraction_vector(&inf->params.point,
			&cls.closest_f->coordinates);
	inf->params.normal = multiply_vector(&inf->params.normal, 1.0
			/ vector_length(&inf->params.normal));
	inf->params.view = multiply_vector(inf->ray, -1);
	color_without_reflection = change_color_intensity(rgb,
			compute_lightning(&inf->params.point,
				&inf->params.normal, &inf->params.view, inf, 100));
	reflection(rgb, &color_without_reflection, inf, depth);
}

void	ray_tracing(t_inf *inf, int mlx_y, int mlx_x, double y)
{
	double		x;
	double		ray_coord[2];
	t_vplane	vplane;
	t_dot		ray;
	t_rgb		color;

	vplane = get_view_plane(WIDTH, HEIGHT, inf->cam.fov);
	while (y > -HEIGHT / 2)
	{
		ray_coord[1] = y * vplane.y_pixel;
		x = -WIDTH / 2;
		mlx_x = -1;
		while (x < WIDTH / 2)
		{
			ray_coord[0] = x * vplane.x_pixel;
			ray = new_dot(ray_coord[0], ray_coord[1], -1);
			normalize_vector(&ray);
			inf->ray = &ray;
			get_color(&inf->cam.view_point, &color,
				RECURSION_DEPTH, inf);
			my_mlx_pixel_put(inf, ++mlx_x, mlx_y,
				create_trgb(0, color.r, color.g, color.b));
			++x;
		}
		++mlx_y;
		--y;
	}
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
}
