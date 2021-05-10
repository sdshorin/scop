
#include "libft.h"

float	ft_float_vector_pop_back(t_float_vector *float_vector)
{
	if (float_vector->size <= 0)
		return ('\0');
	float_vector->size--;
	return (float_vector->data[float_vector->size]);
}
