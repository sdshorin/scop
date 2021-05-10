

#include "libft.h"

int	ft_float_vector_copy(t_float_vector *dst, t_float_vector *src)
{
	size_t i;

	ft_float_vector_reset(dst);
	i = 0;
	while (i < src->size)
	{
		if (ft_float_vector_push_back(dst, src->data[i]))
			return (1);
		i++;
	}
	return (0);
}
