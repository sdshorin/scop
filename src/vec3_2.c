#include "scop.h"

t_vec3	set_vec3(float a, float b, float c, float *dest)
{
	dest[0] = a;
	dest[1] = b;
	dest[2] = c;
	return (dest);
}

t_vec3	copy_vec3_with_offset(float *src, float *dest, int offset)
{
	dest[0] = src[0];
	dest[offset] = src[1];
	dest[2 * offset] = src[2];
	return (dest);
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
	return (dest);
}

t_vec3	vec3_copy(t_vec3 source, t_vec3 dest)
{
	dest[0] = source[0];
	dest[1] = source[1];
	dest[2] = source[2];
	return (dest);
}

t_vec3	vec3_neg(t_vec3 vec)
{
	vec[0] = -vec[0];
	vec[1] = -vec[1];
	vec[2] = -vec[2];
	return (vec);
}
