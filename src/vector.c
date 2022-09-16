#include "minirt.h"

t_dot 	new_dot(double x, double y, double z)
{
	t_dot 	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_rgb 	new_rgb(unsigned char x, unsigned char y, unsigned char z)
{
	t_rgb 	new;

	new.r = x;
	new.g = y;
	new.b = z;
	return (new);
}

t_dot	subtraction_vector(t_dot *vector_a, t_dot *vector_b)         //вычитание векторов
{
	t_dot    vector_c;

	vector_c = new_dot(vector_a->x - vector_b->x, vector_a->y - vector_b->y,
					   vector_a->z - vector_b->z);
	return (vector_c);
}

t_dot    addition_vector(t_dot *vector_a, t_dot *vector_b)         //сложение векторов
{
	t_dot    vector_c;

	vector_c = new_dot(vector_a->x + vector_b->x, vector_a->y + vector_b->y,
					   vector_a->z + vector_b->z);
	return (vector_c);
}

double   vector_length(t_dot *vector)
{
	double length;

	length = sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
	return (length);
}

void    normalize_vector(t_dot *vector)
{
	double   norm;
	double   length;

	length = vector_length(vector);
	norm = 1/length;
	vector->x = vector->x * norm;
	vector->y = vector->y * norm;
	vector->z = vector->z * norm;
}

double   dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b)
{
	double res;

	res = ((vector_a->x * vector_b->x) + (vector_a->y * vector_b->y) + (vector_a->z * vector_b->z));
	/*
	скалярное произведение векторов, но у векторов есть ещё углы ориентации пространства
	пока что косинус этих углов берём равным 1, потом если понадобиться, то надо будет домножать на
	косинус угла между векторов
	*/

	return (res);
}

t_dot	multiply_vector(t_dot *vector, double num)
{
	t_dot	multed;

	multed.x = vector->x * num;
	multed.y = vector->y * num;
	multed.z = vector->z * num;
	return (multed);
}