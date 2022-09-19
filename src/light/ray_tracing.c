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

void	get_color(t_dot *origin, double t_min, double t_max,
					t_rgb *rgb, char depth, t_inf *inf)
{
	t_intersec	cls;
	t_dot		point;
	t_dot		normal;
	t_dot		multed;
	t_dot		view;
	t_rgb		col;
	t_dot	refl_ray;

	cls.t_min = t_min;
	cls.closest_t = t_max;
	cls.closest_f = NULL;
	closest_intersection(origin, inf, &cls);
	if (!cls.closest_f)
	{
		rgb->r = 0;
		rgb->g = 0;
		rgb->b = 0;
		return ;
	}
	rgb->r = cls.closest_f->rgb.r;
	rgb->g = cls.closest_f->rgb.g;
	rgb->b = cls.closest_f->rgb.b;
	multed = multiply_vector(inf->ray, cls.closest_t);
	point = addition_vector(origin, &multed);
	normal = subtraction_vector(&point, &cls.closest_f->coordinates);
	normal = multiply_vector(&normal, 1.0 / vector_length(&normal));
	view = multiply_vector(inf->ray, -1);
//	change_color_intensity(rgb,
	// compute_lightning(&point, &normal, &view, inf, 100));
//	(void)depth;
	col = change_color_intensity(rgb, compute_lightning(&point, &normal, &view, inf, 100));
	if (!depth)
	{
		*rgb = col;
		return;
	}
	refl_ray = reflect_ray(&view, &normal);
	inf->ray = &refl_ray;
	get_color(&point, 1e-10, DBL_MAX, rgb, --depth, inf);
	*rgb = addition_rgb(change_color_intensity(&col, 1 - 0.5),
						 change_color_intensity(rgb, 0.5));
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
			inf->ray = &ray;
			get_color(&inf->cam.view_point, 1, DBL_MAX, &color,
					  RECURSION_DEPTH, inf);
			my_mlx_pixel_put(inf, ++mlx_x, mlx_y, create_trgb(0, color.r, color.g, color.b));
			++x;
		}
		++mlx_y;
		--y;
	}
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
}