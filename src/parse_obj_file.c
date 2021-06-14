#include "scop.h"

t_obj	*create_obj_struct(void)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		exit(0);
	if (ft_float_vector_init(&obj->verticles))
		exit(0);
	if (ft_float_vector_init(&obj->uv))
		exit(0);
	if (ft_float_vector_init(&obj->normals))
		exit(0);
	if (ft_float_vector_init(&obj->vert_buffer))
		exit(0);
	if (ft_float_vector_init(&obj->uv_buffer))
		exit(0);
	if (ft_float_vector_init(&obj->normals_buffer))
		exit(0);
	if (ft_float_vector_init(&obj->colors_buffer))
		exit(0);
	return (obj);
}

void	parse_vector_f(t_float_vector *vec, char *str, size_t vec_size)
{
	size_t	i;

	i = 0;
	while (i++ < vec_size)
	{
		while (*str && *str == ' ' && str++)
			;
		if (ft_float_vector_push_back(vec, (ft_float_atoi(str))))
			exit(1);
		while (*str && (ft_isdigit(*str) || *str == '.' || *str == '-') \
					&& str++)
			;
	}
}

t_obj	*create_object_from_file(int fd)
{
	t_obj	*obj;
	char	*str;

	obj = create_obj_struct();
	if (!obj)
		exit(0);
	while (get_next_line(fd, &str) > 0)
	{
		if (ft_strlen(str) < 2)
			;
		else if (str[0] == 'v' && str[1] == ' ')
			parse_vector_f(&obj->verticles, str + 1, 3);
		else if (str[0] == 'v' && str[1] == 't')
			parse_vector_f(&obj->uv, str + 2, 2);
		else if (str[0] == 'v' && str[1] == 'n')
			parse_vector_f(&obj->normals, str + 2, 3);
		else if (str[0] == 'f')
			parse_figure(obj, str + 1);
		free(str);
	}
	obj->mix_scale = 0.0f;
	close(fd);
	return (obj);
}
