

#include "libft.h"

int		ft_uint_vector_init(t_uint_vector *int_vector)
{
	int_vector->size = 0;
	int_vector->capacity = 16;
	int_vector->data = (unsigned int*)malloc(int_vector->capacity * sizeof(unsigned int));
	if (!int_vector->data)
		return (1);
	return (0);
}
