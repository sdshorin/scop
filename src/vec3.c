#include "scop.h"

t_vec3	vec3_minus(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
	return (dest);
}

t_vec3	vec3_norm(t_vec3 vec)
{
	float	sum;

	sum = vec[0] + vec[1] + vec[2];
	sum = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	if (sum == 0.0)
		return (vec);
	sum = sqrt(sum);
	vec[0] /= sum;
	vec[1] /= sum;
	vec[2] /= sum;
	return (vec);
}

t_vec3	vec3_scale(t_vec3 vec, float scale)
{
	vec[0] = vec[0] * scale;
	vec[1] = vec[1] * scale;
	vec[2] = vec[2] * scale;
	return (vec);
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest)
{
	dest[0] = a[1] * b[2] - a[2] * b[1];
	dest[1] = a[2] * b[0] - a[0] * b[2];
	dest[2] = a[0] * b[1] - a[1] * b[0];
	return (dest);
}

t_vec3	vec3_get_average(t_vec3 vertices, size_t size, t_vec3 result)
{
	size_t	i;

	i = 0;
	result[0] = 0.0f;
	result[1] = 0.0f;
	result[2] = 0.0f;
	while (i < size)
	{
		result[0] += vertices[i * 3];
		result[1] += vertices[i * 3 + 1];
		result[2] += vertices[i * 3 + 2];
		i++;
	}
	result[0] /= size;
	result[1] /= size;
	result[2] /= size;
	return (result);
}
