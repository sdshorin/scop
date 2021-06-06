


#ifndef SCOP_H
#define SCOP_H

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <fcntl.h>
#include "libft.h"


# include <stdio.h>



#define VERTEX_SHADER "./shaders/4.1.materials.vs"
#define FRAGMENT_SHADER "./shaders/4.1.materials.fs"

#define numeric_t float

typedef float *vec3_t;
typedef numeric_t *mat4_t;


typedef struct s_obj {
	t_int_vector triangels;
	t_float_vector verticles;
}  t_obj;

typedef struct s_camera {
	float pos[3];
	float front[3];
	float up[3];
	float proj[16];
	float view[16];


} t_camera;

typedef struct s_buffers {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

} t_buffers;

typedef struct s_env {
	t_obj *object;
	unsigned int shader;
	t_camera camera;
	t_buffers buffs;
	GLFWwindow *window;
}  t_env;


t_obj			*create_object_from_file(int fd);
mat4_t 			mat4_perspective(float h_1, float aspect, float n, float f, float *mat);



unsigned int create_shader(char *path_vertex, char* path_fragment);


vec3_t copy_vec3(float *src, float *dest);
vec3_t set_vec3(float a, float b, float c, float *dest);
vec3_t  vec3_minus(vec3_t a, vec3_t b, vec3_t dest);
vec3_t  vec3_norm(vec3_t vec);
vec3_t  vec3_cross(vec3_t a, vec3_t b, vec3_t dest);
vec3_t  vec3_add(vec3_t a, vec3_t b, vec3_t dest);


mat4_t mat4_identity(float *dest);
mat4_t mat4_perspective(float h_1, float aspect, float n, float f, float *mat);
mat4_t mat4_create_camera_matrix(vec3_t pos, vec3_t target, vec3_t up, mat4_t result);




vec3_t vec3(float a, float b, float c);







#endif