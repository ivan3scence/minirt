#include "minirt.h"

t_dot	new_dot(double x, double y, double z)
{
	t_dot	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_rgb	new_rgb(unsigned char x, unsigned char y, unsigned char z)
{
	t_rgb	new;

	new.r = x;
	new.g = y;
	new.b = z;
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
