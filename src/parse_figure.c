#include "scop.h"

char	*parse_figure_point(t_temp_figure_point *point, char*str)
{
	int				i;
	unsigned int	num;

	i = 0;
	point->p_num = 0;
	point->uv_num = 0;
	point->vn_num = 0;
	while ((ft_isdigit(*str) || *str == '/') && i < 3)
	{
		num = ft_atoi(str) - 1;
		while (ft_isdigit(*str) && str++)
			;
		if (i == 0)
			point->p_num = num;
		else if (i == 1)
			point->uv_num = num;
		else if (i == 2)
			point->vn_num = num;
		if (*str == '/' && str++)
			;
		i++;
	}
	return (str);
}

void	copy_figure_point(t_temp_figure_point *dest,
							t_temp_figure_point *source)
{
	dest->p_num = source->p_num;
	dest->uv_num = source->uv_num;
	dest->vn_num = source->vn_num;
}

void	copy_point(t_float_vector *source, t_float_vector *des,
								unsigned int index, unsigned int len)
{
	unsigned int		i;
	float				temp;

	i = 0;
	if (source->size <= index + len - 1)
		exit_error("Error: problem in model");
	while (i < len)
	{
		temp = source->data[index + i];
		if (ft_float_vector_push_back(des, temp))
			exit_error("Error: can't add elem to float vector");
		i++;
	}
}

void	add_triangle(t_obj *obj, t_temp_figure_point *p)
{
	int		i;
	float	triangle_color;

	i = 0;
	triangle_color = ((float)(rand()) / 0x7fffffff) / 1.0;
	while (i < 3)
	{
		copy_point(&obj->verticles, &obj->vert_buffer, p[i].p_num * 3, 3);
		if (obj->uv.size)
			copy_point(&obj->uv, &obj->uv_buffer, p[i].uv_num * 2, 2);
		else
			copy_point(&obj->verticles, &obj->uv_buffer, p[i].p_num * 3, 2);
		if (obj->normals.size)
			copy_point(&obj->normals, &obj->normals_buffer, p[i].vn_num * 3, 3);
		if (ft_float_vector_push_back(&obj->colors_buffer, triangle_color))
			exit_error("Error: can't add elem to colors_buffer");
		i ++;
	}
}

void	parse_figure(t_obj *obj, char *str)
{
	t_temp_figure_point	p[3];
	int					point_num;

	point_num = 0;
	while (*str)
	{
		while (*str && *str == ' ' && str++)
			;
		if (!ft_isdigit(*str))
			return ;
		if (point_num == 0)
			str = parse_figure_point(p, str);
		else
			str = parse_figure_point((p + 2), str);
		if (point_num >= 2)
			add_triangle(obj, p);
		copy_figure_point((p + 1), (p + 2));
		point_num++;
	}
}
