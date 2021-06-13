


#ifndef SCOP_H
#define SCOP_H

#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
# define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include <fcntl.h>
#include "libft.h"
#include <math.h>



#include <unistd.h>
#include <stdio.h>
#include <limits.h>


# define CAMERA_SENSITIVITY 0.05f
#define PI 3.14159265


int current_path(int i);
void check_error(int i);
void print_matrix(char *name, float *mat);
void print_obj_array(float *data, size_t size, size_t on_line);







#define VERTEX_SHADER "shaders/4.1.materials.vs"
#define FRAGMENT_SHADER "shaders/4.1.materials.fs"

#define numeric_t float

typedef float *vec3_t;
typedef numeric_t *mat4_t;

struct s_camera;
typedef struct s_obj {
	t_float_vector verticles; // v
	t_float_vector uv; // vt
	t_float_vector normals; // vn
	t_float_vector vert_buffer; // v
	t_float_vector uv_buffer; // v
	t_float_vector normals_buffer; // v
	t_float_vector colors_buffer;

	float model[16];
}  t_obj;

typedef struct s_camera_look {
	float last_x;
	float last_y;
	int is_inited;
	float yaw; // по горизонтали
	float pitch; // по вертикали
	struct s_camera *camera;

} t_camera_look ;


typedef struct s_camera {
	float pos[3];
	float front[3];
	float up[3];
	float proj[16];
	float view[16];
	t_camera_look *look;

} t_camera;

typedef struct s_buffers {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int cbo;

} t_buffers;

typedef struct s_env {
	t_obj *object;
	unsigned int shader;
	t_camera camera;
	t_buffers buffs;
	GLFWwindow *window;
}  t_env;


t_obj			*create_object_from_file(int fd);

void exit_error(char *error);


unsigned int create_shader(char *path_vertex, char* path_fragment);


vec3_t copy_vec3(float *src, float *dest);
vec3_t set_vec3(float a, float b, float c, float *dest);
vec3_t  vec3_minus(vec3_t a, vec3_t b, vec3_t dest);
vec3_t  vec3_norm(vec3_t vec);
vec3_t vec3_scale(vec3_t vec, float scale);
vec3_t vec3_copy(vec3_t source, vec3_t dest);
vec3_t vec3_neg(vec3_t vec);


vec3_t  vec3_cross(vec3_t a, vec3_t b, vec3_t dest);
vec3_t  vec3_add(vec3_t a, vec3_t b, vec3_t dest);
vec3_t copy_vec3_with_offset(float *src, float *dest, int offset);


mat4_t mat4_identity(float *dest);
mat4_t mat4_perspective(float fov, float aspect, float n, float f, float *mat);
mat4_t mat4_create_camera_matrix(vec3_t pos, vec3_t target, vec3_t up, mat4_t result);
float *mat4_scale(float *mat, float scale);
mat4_t  mat4_mult(mat4_t a, mat4_t b, mat4_t result);

mat4_t mat4_rotate_model_y(mat4_t model, float rotate);

mat4_t mat4_offset(vec3_t offset, mat4_t dest);


vec3_t vec3(float a, float b, float c);

vec3_t  vec3_get_average(vec3_t vertices, size_t size, vec3_t result);






#endif