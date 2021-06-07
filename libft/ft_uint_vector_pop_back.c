
#include "libft.h"

unsigned int	ft_uint_vector_pop_back(t_uint_vector *int_vector)
{
	if (int_vector->size <= 0)
		return ('\0');
	int_vector->size--;
	return (int_vector->data[int_vector->size]);
}
