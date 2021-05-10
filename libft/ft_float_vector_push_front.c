
#include "libft.h"

int	ft_float_vector_push_front(t_float_vector *float_vector, float new_num)
{
	float		last_elem;
	size_t	i;

	if (float_vector->size > 0)
	{
		i = 0;
		last_elem = float_vector->data[float_vector->size - 1];
		while (i < float_vector->size - 1)
		{
			float_vector->data[i + 1] = float_vector->data[i];
			i++;
		}
		float_vector->data[0] = new_num;
		if (ft_float_vector_push_back(float_vector, last_elem))
			return (1);
	}
	else
	{
		if (ft_float_vector_push_back(float_vector, new_num))
			return (1);
	}
	return (0);
}
