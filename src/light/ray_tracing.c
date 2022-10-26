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

double	*intersect_ray_plane(t_dot *o, t_dot *ray, t_dot *coordinates, t_dot *orientation_vec, t_inf *inf)
{
	t_dot	hui;
	double	*tt;
	double	denom;

	tt = (double *)malloc(sizeof(double) * 2);
	if (!tt)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	denom = dot_product_of_vectors(orientation_vec, ray);
	if (denom == 0)
		return (tt);
	hui = subtraction_vector(coordinates, o);
	tt[0] = dot_product_of_vectors(&hui, orientation_vec) / denom;
	if (tt[0] <= 0)
		tt[0] = DBL_MAX;
	return (tt);
}

static void	normilize_cy(double *tt, t_dot *o, t_dot *d, t_inf *inf, t_figure *cyl)
{
	double	dist;
	double	t;

	if ((cyl->dist1 >= 0 && cyl->dist1 <= cyl->height
			&& tt[0] > EPSILON) && (cyl->dist2 >= 0
			&& cyl->dist2 <=cyl->height && tt[1] > EPSILON))
	{
		dist = cyl->dist2;
		t = tt[1];
		if (tt[0] < tt[1])
		{
			t = tt[0];
			dist = cyl->dist1;
		}
	}
	else if (cyl->dist1 >= 0 && cyl->dist1 <= cyl->height
				&& tt[0] > EPSILON)
	{
		dist = cyl->dist1;
		t = tt[0];
	}
	else
	{
		dist = cyl->dist2;
		t = tt[1];
	}
	tt[0] = t;
	t_dot	mult=multiply_vector(d, t);
	t_dot	mult2=multiply_vector(&cyl->orientation_vec, dist);
	t_dot	sub2=subtraction_vector(&cyl->coordinates, o);
	t_dot	sub=subtraction_vector(&mult, &mult2);
	cyl->normal = subtraction_vector(&sub, &sub2);
	normalize_vector(&cyl->normal);
}

static void	disks(t_dot o, t_dot *d, t_figure *cyl, t_inf *inf, double *tt)
{
	t_dot	sub=subtraction_vector(&cyl->coordinates, &o);
	t_dot	mult=multiply_vector(d, tt[0]);
	t_dot	sub2=subtraction_vector(&mult, &sub);

	cyl->dist1 = dot_product_of_vectors(&cyl->orientation_vec, &sub2);

	mult=multiply_vector(d, tt[1]);
	sub2=subtraction_vector(&mult, &sub);
	cyl->dist2 = dot_product_of_vectors(&cyl->orientation_vec, &sub2);
	if (!((cyl->dist1 >= 0 && cyl->dist1 <= cyl->height
					&& tt[0] > EPSILON) || (cyl->dist2 >= 0 && cyl->dist2 <= cyl->height
					&& tt[1] > EPSILON)))
	{
		tt[0] = DBL_MAX;
		tt[1] = DBL_MAX;
	}
	else
		normilize_cy(tt, &o, d, inf, cyl);
}

static double	*cap_intersection(t_dot *o, t_dot *d, t_figure *cyl, t_inf *inf, double *tt)
{
	double	id1;
	double	*id;
	double	id2;
	t_dot	ip1;
	t_dot	ip2;
	t_dot	c2;

	ip1 = multiply_vector(&cyl->orientation_vec, cyl->height);
	c2 = addition_vector(&cyl->coordinates, &ip1);
	id = intersect_ray_plane(o, d, &cyl->coordinates, &cyl->orientation_vec, inf);
	id1 = id[0] < id[1] ? id[0] : id[1];
	id = intersect_ray_plane(o, d, &c2, &cyl->orientation_vec, inf);
	id2 = id[0] < id[1] ? id[0] : id[1];
	if (id1 < DBL_MAX || id2 < DBL_MAX)
	{
		t_dot	mult=multiply_vector(d, id1);
		ip1 = addition_vector(o, &mult);
		mult=multiply_vector(d, id2);
		ip2 = addition_vector(o, &mult);
		if ((id1 < DBL_MAX && distance(ip1, cyl->coordinates) <= cyl->radius)
				&& (id2 < DBL_MAX && distance(ip2, c2) <= cyl->radius))
		{
			tt[0] = id1;
			tt[1] = id2;
			return (tt);
		}
		else if (id1 < DBL_MAX && distance(ip1, cyl->coordinates) <= cyl->radius)
		{
			tt[1] = DBL_MAX;
			tt[0] = id1;
			return (tt);
		}
		else if (id2 < DBL_MAX && distance(ip2, c2) <= cyl->radius)
		{
			tt[1] = DBL_MAX;
			tt[0] = id2;
			return (tt);
		}
		else
		{
			tt[0] = DBL_MAX;
			tt[1] = DBL_MAX;
			return (tt);
		}
	}
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	return (tt);
}

double	*intersect_ray_cylinder(t_dot o, t_dot *d, t_figure *cyl,
									t_inf *inf)
{
	double	b;
	double	c;
	double	a;
	double	disc;
	double	*tt;
	double	tmp;
	t_dot	cross2;
	t_elem	el;

	tt = (double *)malloc(sizeof(double) * 2);
	if (!tt)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	el.cross = vec_cross(d, &cyl->orientation_vec);
	cross2 = vec_cross(&o, &cyl->orientation_vec);
	a = dot_product_of_vectors(&el.cross, &el.cross);
	b = 2 * dot_product_of_vectors(&cross2, &el.cross);
	c = dot_product_of_vectors(&cross2, &cross2) - (cyl->radius * cyl->radius
		* dot_product_of_vectors(&cyl->orientation_vec, &cyl->orientation_vec));
	disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (tt);
	tt[0] = (-b - sqrt(disc)) / (2 * a);
	tt[1] = (-b + sqrt(disc)) / (2 * a);
	//if (tt[0] == DBL_MAX && tt[1] == DBL_MAX)
	//	return (tt);
	disks(o, d, cyl, inf, tt);
	double	*tt2=(double*)malloc(sizeof(double)*2);
	cap_intersection(&o, d, cyl, inf, tt2);
	double min=tt[0]<tt[1]?tt[0]:tt[1];
	double min2=tt2[0]<tt2[1]?tt2[0]:tt2[1];
	tt[1] = DBL_MAX;
	tt[0] = min;
	if (min2 < min)
		tt[0] = min2;
	return (tt);
}

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
		- sphere->radius * sphere->radius;
	disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (tt);
	tt[0] = (-b - sqrt(disc)) / (2 * a);
	tt[1] = (-b + sqrt(disc)) / (2 * a);
	//printf("%g:%g\n", tt[0], tt[1]);
	return (tt);
}

double	*intersect_ray_cone(t_dot cam, t_dot *ray,
t_figure *cone, t_inf *inf)
{
	double	b;
	double	c;
	double	a;
	double	disc;
	double	*tt;
	double	tan;

	tt = (double *)malloc(sizeof(double) * 2);
	if (!tt)
		free_exit(MALLOC, inf, MALLOC_ERROR);
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	tan = cone->radius * cone->radius / cone->height / cone->height;
	a = cone_dot_product_of_vectors(ray, ray, tan);
	b = 2 * cone_dot_product_of_vectors(&cam, ray, tan);
	c = cone_dot_product_of_vectors(&cam, &cam, tan);
	disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (tt);
	tt[0] = (-b - sqrt(disc)) / (2 * a);
	tt[1] = (-b + sqrt(disc)) / (2 * a);
	double y1 = cam.y + tt[0] * ray->y;
	double y2 = cam.y + tt[1] * ray->y;
	double ymin = cone->coordinates.y - cone->height;
	double ymax = cone->coordinates.y;
	if (y1 < ymin || y1 > ymax || y2 < ymin || y2 > ymax)
	{
		tt[0] = DBL_MAX;
		tt[1] = DBL_MAX;
	}
	if ((y1 < y2 && y1 < ymin && y2 > ymin) || (y1 > y2 && y2 < ymin && y1 > ymin))
		tt[0] = (ymin - cam.y) / ray->y;
	return (tt);
}
void	closest_figure(t_dot *origin, t_figure *figure, t_inf *inf, t_intersec *cls)
{
	double	*tt;

	if (figure->type == SPHERE_TYPE)
		tt = intersect_ray_sphere(subtraction_vector(origin,
					&figure->coordinates), inf->ray, figure, inf);
	else if (figure->type == CYLINDER_TYPE)
		tt = intersect_ray_cylinder(subtraction_vector(origin,
					&figure->coordinates), inf->ray, figure, inf);
	else if (figure->type == CONE_TYPE)
		tt = intersect_ray_cone(subtraction_vector(origin,
					&figure->coordinates), inf->ray, figure, inf);
	else if (figure->type == PLANE_TYPE)
		tt = intersect_ray_plane(&inf->cam.view_point, inf->ray, &figure->coordinates, &figure->orientation_vec, inf);
	else
		return ;
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
	t_figure	*figure;

	figure = inf->figures;
	while (figure)
	{
		closest_figure(origin, figure, inf, cls);
		figure = figure->next;
	}
}

void	background(t_rgb *rgb)
{
	rgb->r = 0;
	rgb->g = 0;
	rgb->b = 0;
}

char	is_intersect(t_intersec *cls, t_inf *inf, t_dot *origin, double flag)
{
	cls->t_min = (double)flag * 1e-10 + (!flag) * 1e-2;
	cls->closest_t = (double)flag * DBL_MAX + (!flag) * 1.0;
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

	if (!is_intersect(&cls, inf, origin, 1))
		return (background(rgb));
	*rgb = cls.closest_f->rgb;
	//inf->params.multed = multiply_vector(inf->ray, cls.closest_t);
	//inf->params.point = addition_vector(origin, &inf->params.multed);
	//inf->params.normal = subtraction_vector(&inf->params.point,
	//		&cls.closest_f->coordinates);
	//inf->params.normal = multiply_vector(&inf->params.normal, 1.0
	//		/ vector_length(&inf->params.normal));
	//inf->params.view = multiply_vector(inf->ray, -1);
	//color_without_reflection = change_color_intensity(rgb,
	//		compute_lightning(subtraction_vector(&inf->light.l_point,
	//				&inf->params.normal), inf, 100));
	//if (depth == START_RECURSION)
	//{
	//	// if (cls.closest_f->type == CONE_TYPE)
	//		// printf("ura");
	//	depth = cls.closest_f->refl;
	//}
	//if (depth > 0)
	//	reflection(rgb, &color_without_reflection, inf, --depth);
	//else
	//	*rgb = color_without_reflection;
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
				START_RECURSION, inf);
			my_mlx_pixel_put(inf, ++mlx_x, mlx_y,
				create_trgb(0, color.r, color.g, color.b));
			++x;
		}
		++mlx_y;
		--y;
	}
	mlx_put_image_to_window(inf->mlx, inf->win, inf->img, 0, 0);
}
