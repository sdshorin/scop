/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:02:59 by kpsylock          #+#    #+#             */
/*   Updated: 2021/05/10 13:40:33 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// static int		mode_switcher(t_data *data, char *str)
// {
// 	if (data->start == NULL || data->end == NULL)
// 	{
// 		ft_strdel(&str);
// 		error_handler("No start/end mark!", data);
// 	}
// 	return (1);
// }

// int				read_comments(t_data *data, char **str)
// {
// 	int comm;

// 	comm = 0;
// 	get_input(*str, data);
// 	if (str[1] != '\0')
// 	{
// 		if (ft_strequ(&((*str)[2]), "start"))
// 			comm = 1;
// 		else if (ft_strequ(&((*str)[2]), "end"))
// 			comm = -1;
// 	}
// 	return (comm);
// }

// static t_data	*finish_reading(t_data *data, char **str)
// {
// 	ft_strdel(str);
// 	return (data);
// }

void parse_verticles(t_obj *obj, char *str)
{
	int i;

	i = 0;
	str++;
	while (i++ < 3)
	{
		// проверить, что будет в случае исключений!!
		while (*str && *str == ' ' && str++);
		ft_float_vector_push_back(&obj->verticles, ft_float_atoi(str));
		while (*str && (ft_isdigit(*str) || *str == '.' || *str == '-') && str++);
	}
}

void parse_triangle(t_obj *obj, char *str)
{
	int i;

	i = 0;
	str++;
	while (i++ < 3)
	{
		// проверить, что будет в случае исключений!!
		while (*str && *str == ' ' && str++);
		ft_int_vector_push_back(&obj->triangels, ft_float_atoi(str));
		while (*str && (ft_isdigit(*str)) && str++);
	}
}

t_obj *create_obj_struct()
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		exit(0);
	if (ft_float_vector_init(&obj->verticles))
		exit(0);
	if (ft_int_vector_init(&obj->triangels))
		exit(0);
	return (obj);
}


t_obj			*create_object_from_file(int fd)
{
	t_obj	*obj;
	char	*str;
	
	if (!(obj = create_obj_struct()))
		exit(0);

	while (get_next_line(fd, &str) > 0)
	{
		if (ft_strlen(str) < 1)  // < 2?????  "\n\0"
			continue ;
		else if (str[0] == 'v')
			parse_verticles(obj, str);
		else if (str[0] == 'f')
			parse_triangle(obj, str);
		// parse normals, textures, materials, ...

		free(str);
	}
	return (obj);
}
