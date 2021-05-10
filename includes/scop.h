


#ifndef SCOP_H
#define SCOP_H

#include "libft.h"

typedef struct s_obj {
	t_int_vector triangels;
	t_float_vector verticles;
}  t_obj;

typedef struct s_env {
	t_obj *object;
}  t_env;


t_obj			*create_object_from_file(int fd);





#endif