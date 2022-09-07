#include "minirt.h"


t_sphere	**get_spheres(void)
{
	t_sphere	**spheres;

	spheres = (t_sphere **)malloc(sizeof(t_sphere *) * 4);
	if (!spheres)
		exit(1);
	spheres[0] = (t_sphere *)malloc(sizeof(t_sphere));
	spheres[0]->center.x = 0;
	spheres[0]->center.y = -1;
	spheres[0]->center.z = 3;
	spheres[0]->radius = 1;
	spheres[0]->color.r = 255;
	spheres[0]->color.g = 0;
	spheres[0]->color.b = 0;
	spheres[1] = (t_sphere *)malloc(sizeof(t_sphere));
	spheres[1]->center.x = -2;
	spheres[1]->center.y = 1;
	spheres[1]->center.z = 3;
	spheres[1]->radius = 1;
	spheres[1]->color.r = 0;
	spheres[1]->color.g = 255;
	spheres[1]->color.b = 0;
	spheres[2] = (t_sphere *)malloc(sizeof(t_sphere));
	spheres[2]->center.x = 2;
	spheres[2]->center.y = 1;
	spheres[2]->center.z = 3;
	spheres[2]->radius = 1;
	spheres[2]->color.r = 0;
	spheres[2]->color.g = 0;
	spheres[2]->color.b = 255;
	spheres[3] = NULL;
	return (spheres);
}

int	create_trgb(int t, int r, int g, int b)
{
	//printf("%d %d %d %d\n", t, r, g, b);
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

t_dot	canvas_to_viewpoint(double x, double y)
{
	t_dot	viewport={5 * x * CANVAS_WIDTH / WIDTH, 5 * y * CANVAS_HEIGHT / HEIGHT,
		5 * CANVAS_Z};
	return (viewport);
}

double	v_mult(t_dot v1, t_dot v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_dot	vector(t_dot d1, t_dot d2)
{
	t_dot	vec;

	vec.x = d2.x - d1.x;
	vec.y = d2.y - d1.y;
	vec.z = d2.z - d1.z;
	return (vec);
}

double	*intersect_ray_sphere(t_dot o, t_dot d, t_sphere *sphere)
{
	t_dot	oc;
	double	dis;
	double	*tt;

	tt = (double *)malloc(sizeof(double) * 2);
	if (!tt)
		exit(1);
	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	oc = vector(o, sphere->center);
	dis = pow(2 * v_mult(oc, d), 2) - 4 * v_mult(d, d) *
		(v_mult(oc, oc) - sphere->radius * sphere->radius);
	if (dis < 0)
	{
	//printf("gg\n");
		return (tt);
	}
	tt[0] = (-2 * v_mult(oc, d) + sqrt(dis)) / (2 * v_mult(d, d));
	tt[1] = (-2 * v_mult(oc, d) - sqrt(dis)) / (2 * v_mult(d, d));
	//printf("%g, %g\n", tt[0], tt[1]);
	return (tt);
}

t_intersec	closest_intersection(t_dot o, t_dot d, double t_min, double t_max,
		t_mlx *mlx)
{
	t_intersec	cls;
	int			i=-1;
	double		*tt;

	cls.closest_sphere = NULL;
	cls.closest_t = DBL_MAX;
	while (mlx->spheres[++i])
	{
		tt = intersect_ray_sphere(o, d, mlx->spheres[i]);
		if (tt[0] >= t_min && tt[0] <= t_max && tt[0] < cls.closest_t)
		{
			//if (tt[0] != DBL_MAX)
			//	printf("gg%g, %g, %g\n", tt[0], tt[1], cls.closest_t);
			cls.closest_t = tt[0];
			cls.closest_sphere = mlx->spheres[i];
			//if (tt[0] != DBL_MAX)
			//	printf("gg%g, %g, %g\n", tt[0], tt[1], cls.closest_t);
		}
		if (tt[1] >= t_min && tt[1] <= t_max && tt[1] < cls.closest_t)
		{
			//printf("%g, %g, %g\n", tt[0], tt[1], cls.closest_t);
			cls.closest_t = tt[1];
			cls.closest_sphere = mlx->spheres[i];
		}
		free(tt);
	}
	return (cls);
}

t_rgb	trace_ray(t_dot o, t_dot d, double t_min, double t_max, t_mlx *mlx)
{
	t_intersec	cls;
	t_rgb		rgb={0,0,0};

	cls = closest_intersection(o, d, t_min, t_max, mlx);
	if (!cls.closest_sphere)
		return (rgb);
	return (cls.closest_sphere->color);
}

void	start_point(t_mlx *mlx)
{
	int		x;
	int		y;
	t_dot	d;
	t_dot cam={0,0,0};
	t_rgb	color;

	x = -WIDTH / 2;
	mlx->spheres = get_spheres();
	while (x < WIDTH / 2)
	{
		y = -HEIGHT / 2;
		while (y < HEIGHT / 2)
		{
			d = canvas_to_viewpoint(x, y);
			color = trace_ray(cam, d, -5, DBL_MAX, mlx);
			my_mlx_pixel_put(mlx, x + WIDTH / 2, y + HEIGHT / 2,
				create_trgb(0x0, color.r, color.g, color.b));
			++y;
		}
		++x;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return ;
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1920, 1080, "miniRT");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_length,
			&mlx.endian);
	start_point(&mlx);
	mlx_loop(mlx.mlx);
}
