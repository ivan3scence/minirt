#include "minirt.h"

t_dot	new_dot(double x, double y, double z)
{
	t_dot	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_rgb	new_rgb(double x, double y, double z, t_inf *inf)
{
	t_rgb	new;

	if (x < 0 || y < 0 || z < 0)
		free_exit(INCORRECT_RGB, inf, SYNTAX_ERROR);
	new.r = (unsigned char)x % 256;
	new.g = (unsigned char)y % 256;
	new.b = (unsigned char)z % 256;
	return (new);
}

t_dot	subtraction_vector(t_dot *vector_a, t_dot *vector_b)
{
	return (new_dot(vector_a->x - vector_b->x, vector_a->y - vector_b->y,
			vector_a->z - vector_b->z));
}

t_dot	addition_vector(t_dot *vector_a, t_dot *vector_b)
{
	t_dot	vector_c;

	vector_c = new_dot(vector_a->x + vector_b->x, vector_a->y + vector_b->y,
			vector_a->z + vector_b->z);
	return (vector_c);
}

double	vector_length(t_dot *vector)
{
	double	length;

	length = sqrt((vector->x * vector->x)
			+ (vector->y * vector->y) + (vector->z * vector->z));
	return (length);
}

void	normalize_vector(t_dot *vector)
{
	double	norm;
	double	length;

	length = vector_length(vector);
	norm = 1 / length;
	vector->x = vector->x * norm;
	vector->y = vector->y * norm;
	vector->z = vector->z * norm;
}

double	dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b)
{
	double	res;

	res = ((vector_a->x * vector_b->x) + (vector_a->y * vector_b->y)
			+ (vector_a->z * vector_b->z));
	return (res);
}

double	cyl_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b)
{
	return ((vector_a->x * vector_b->x) + (vector_a->z * vector_b->z));
}

double	cone_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b, double tan)
{
	return (vector_a->x * vector_b->x + vector_a->z * vector_b->z - tan * vector_a->y * vector_b->y);
}

t_dot	multiply_vector(t_dot *vector, double num)
{
	t_dot	multed;

	multed.x = vector->x * num;
	multed.y = vector->y * num;
	multed.z = vector->z * num;
	return (multed);
}

t_dot	vec_cross(t_dot *vector_a, t_dot *vector_b)
{
	t_dot	v;

	v.x = vector_a->y * vector_b->z - vector_a->z * vector_b->y;
	v.y = vector_a->z * vector_b->x - vector_a->x * vector_b->z;
	v.z = vector_a->x * vector_b->y - vector_a->y * vector_b->x;
	return (v);
}

t_dot	vec_add(t_dot vector_a, t_dot vector_b)
{
	t_dot	v;

	v.x = vector_a.x + vector_b.x;
	v.y = vector_a.y + vector_b.y;
	v.z = vector_a.z + vector_b.z;
	return (v);
}

double	distance(t_dot p1, t_dot p2)
{
	double d;

	d = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2));
	return (d);
}

void	ft_get_normal(t_ray ray, t_dot obj_pos,
		t_inter_point *inter_point)
{
	ray.direction.x *= inter_point->t;
	ray.direction.y *= inter_point->t;
	ray.direction.z *= inter_point->t;
	inter_point->coord = addition_vector(&ray.origin, &ray.direction);
	inter_point->normal = subtraction_vector(&inter_point->coord, &obj_pos);
	normalize_vector(&inter_point->normal);
}

t_dot	sub(t_dot a, t_dot b)
{
	t_dot vect;

	vect.x = a.x - b.x;
	vect.y = a.y - b.y;
	vect.z = a.z - b.z;
	return (vect);
}

double	dot(t_dot a, t_dot b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	get_norm(t_dot vect)
{
	return (sqrt(dot(vect, vect)));
}

t_dot	ft_scale(t_dot a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return (a);
}

t_dot	add(t_dot a, t_dot b)
{
	t_dot vect;

	vect.x = a.x + b.x;
	vect.y = a.y + b.y;
	vect.z = a.z + b.z;
	return (vect);
}

t_dot	normalize(t_dot a)
{
	t_dot vect;
	double len;

	len = get_norm(a);
	vect.x = a.x / len;
	vect.y = a.y / len;
	vect.z = a.z / len;
	return (vect);
}

