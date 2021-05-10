
#include "libft.h"

int		ft_float_vector_init(t_float_vector *float_vector)
{
	float_vector->size = 0;
	float_vector->capacity = 16;
	float_vector->data = (float*)malloc(float_vector->capacity * sizeof(float));
	if (float_vector->data)
		return (0);
	return (1);
}
