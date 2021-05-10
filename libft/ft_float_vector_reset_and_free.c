
#include "libft.h"

void	ft_float_vector_free(t_float_vector *float_vector)
{
	free(float_vector->data);
}

void	ft_float_vector_reset(t_float_vector *src)
{
	src->size = 0;
}
