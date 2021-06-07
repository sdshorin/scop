
#include "libft.h"

int	ft_uint_vector_push_back(t_uint_vector *int_vector, unsigned int i)
{
	unsigned int	*new_data;

	if (int_vector->size < int_vector->capacity)
	{
		int_vector->data[int_vector->size] = i;
		int_vector->size++;
		return (0);
	}
	int_vector->capacity *= 2;
	new_data = (unsigned int*)malloc(int_vector->capacity * sizeof(unsigned int));
	if (!new_data)
		return (1);
	ft_memcpy(new_data, int_vector->data,
		(int_vector->capacity / 2) * sizeof(unsigned int));
	free(int_vector->data);
	int_vector->data = new_data;
	int_vector->data[int_vector->size] = i;
	int_vector->size++;
	return (0);
}
