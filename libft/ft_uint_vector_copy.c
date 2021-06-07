

#include "libft.h"

int	ft_uint_vector_copy(t_uint_vector *dst, t_uint_vector *src)
{
	size_t i;

	ft_uint_vector_reset(dst);
	i = 0;
	while (i < src->size)
	{
		if (ft_uint_vector_push_back(dst, src->data[i]))
			return (1);
		i++;
	}
	return (0);
}
