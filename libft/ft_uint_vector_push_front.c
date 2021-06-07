
#include "libft.h"

int	ft_uint_vector_push_front(t_uint_vector *int_vector, unsigned int new_num)
{
	unsigned int		last_elem;
	size_t	i;

	if (int_vector->size > 0)
	{
		i = 0;
		last_elem = int_vector->data[int_vector->size - 1];
		while (i < int_vector->size - 1)
		{
			int_vector->data[i + 1] = int_vector->data[i];
			i++;
		}
		int_vector->data[0] = new_num;
		if (ft_uint_vector_push_back(int_vector, last_elem))
			return (1);
	}
	else
	{
		if (ft_uint_vector_push_back(int_vector, new_num))
			return (1);
	}
	return (0);
}
