


#ifndef SCOP_H
#define SCOP_H

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>


#include "libft.h"

#define VERTEX_SHADER = "./shaders/4.1.materials.vs"
#define FRAGMENT_SHADER = "./shaders/4.1.materials.fs"

typedef struct s_obj {
	t_int_vector triangels;
	t_float_vector verticles;
}  t_obj;

typedef struct s_camera {
	float pos[3];
	float front[3];
	float up[3];
	float view[16];


} t_camera;

typedef struct s_env {
	t_obj *object;
	unsigned int shader;
	t_camera camera;
}  t_env;
#define numeric_t float


t_obj			*create_object_from_file(int fd);





#endif