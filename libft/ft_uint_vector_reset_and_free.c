
#include "libft.h"

void	ft_uint_vector_free(t_uint_vector *int_vector)
{
	free(int_vector->data);
}

void	ft_uint_vector_reset(t_uint_vector *src)
{
	src->size = 0;
}
