
#include "libft.h"

int	ft_float_vector_push_back(t_float_vector *float_vector, float i)
{
	float	*new_data;

	if (float_vector->size < float_vector->capacity)
	{
		float_vector->data[float_vector->size] = i;
		float_vector->size++;
		return (0);
	}
	float_vector->capacity *= 2;
	new_data = (float*)malloc(float_vector->capacity * sizeof(float));
	if (!new_data)
		return (1);
	ft_memcpy(new_data, float_vector->data,
		(float_vector->capacity / 2) * sizeof(float));
	free(float_vector->data);
	float_vector->data = new_data;
	float_vector->data[float_vector->size] = i;
	float_vector->size++;
	return (0);
}
