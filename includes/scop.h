#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION
# ifdef __APPLE__

// #  define __gl_h_
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
# endif

# include <GLFW/glfw3.h>
# include <OpenGL/gl3.h>

# include <fcntl.h>
# include "libft.h"
# include <math.h>
# include <fcntl.h>
# include <sys/stat.h>

# include <unistd.h>
# include <stdio.h>
# include <limits.h>

# define CAMERA_SENSITIVITY 0.05f
# define PI 3.14159265

# define TEXTURE_PATH "res/da.bmp"

# define VERTEX_SHADER "shaders/4.1.scop.vs"
# define FRAGMENT_SHADER "shaders/4.1.scop.fs"

# define VERTEX_SHADER_NO_LIGHT "shaders/4.1.scop_base.vs"
# define FRAGMENT_SHADER_NO_LIGHT "shaders/4.1.scop_base.fs"

typedef float	*t_vec3;
typedef float	*t_mat4;

typedef struct s_obj {
	t_float_vector	verticles;
	t_float_vector	uv;
	t_float_vector	normals;
	t_float_vector	vert_buffer;
	t_float_vector	uv_buffer;
	t_float_vector	normals_buffer;
	t_float_vector	colors_buffer;
	float			mix_scale;
	float			model[16];
}				t_obj;
struct			s_camera;

typedef struct s_camera_look {
	float			last_x;
	float			last_y;
	int				is_inited;
	float			yaw;
	float			pitch;
	struct s_camera	*camera;
}				t_camera_look;

typedef struct s_camera {
	float			pos[3];
	float			front[3];
	float			up[3];
	float			*proj;
	float			view[16];
	t_camera_look	*look;
}					t_camera;

typedef struct s_buffers {
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	cbo;
	unsigned int	uvbo;
	unsigned int	nbo;
	unsigned int	texture;
}				t_buffers;

typedef struct s_texture {
	int				width;
	int				height;
	unsigned char	*data;
	int				image_size;
}				t_texture;

typedef struct s_env {
	t_obj			*object;
	unsigned int	shader;
	t_camera		camera;
	t_buffers		buffs;
	t_texture		texture;
	GLFWwindow		*window;
	int				with_light;
}				t_env;

typedef struct s_temp_figure_point {
	unsigned int	p_num;
	unsigned int	uv_num;
	unsigned int	vn_num;
}				t_temp_figure_point;

t_obj			*create_object_from_file(int fd);
int				parse_bmp_file(int fd, t_texture *texture);

void			check_error(int i);
void			exit_error(char *error);

unsigned int	create_shader(char *path_vertex, char *path_fragment);

void			process_input(GLFWwindow *window, t_env *env, float delta_time);
void			mouse_callback(GLFWwindow *window, double x_pos, double y_pos);
void			init_positions(t_env *env);
void			init_app(t_env *env);
void			init_camera_look(t_camera_look *look, double x_pos, \
														double y_pos);
t_camera_look	*get_camera_look(void);
void			exit_error(char *error);

void			check_error(int i);
void			free_memory(t_env *env);
int				open_file(char *path, int error_exit);
int				is_regular_file(const char *path);

void			parse_figure(t_obj *obj, char *str);

GLint			get_l(int shader, char *name);
void			start_main_loop(t_env *env);

void			load_texture_to_gpu(t_env *env);
void			load_buffers_to_gpu(t_env *env);
void			load_obj_to_gpu(t_env *env);
void			init_light_shader(t_env *env);
void			init_uniforms(t_env *env);

t_vec3			copy_vec3(float *src, float *dest);
t_vec3			set_vec3(float a, float b, float c, float *dest);
t_vec3			vec3_minus(t_vec3 a, t_vec3 b, t_vec3 dest);
t_vec3			vec3_norm(t_vec3 vec);
t_vec3			vec3_scale(t_vec3 vec, float scale);
t_vec3			vec3_copy(t_vec3 source, t_vec3 dest);
t_vec3			vec3_neg(t_vec3 vec);

t_vec3			vec3_cross(t_vec3 a, t_vec3 b, t_vec3 dest);
t_vec3			vec3_add(t_vec3 a, t_vec3 b, t_vec3 dest);
t_vec3			copy_vec3_with_offset(float *src, float *dest, int offset);

t_mat4			mat4_identity(float *dest);
t_mat4			mat4_perspective(float fov, float aspect, float n, float f);
t_mat4			mat4_create_camera_matrix(t_vec3 pos, t_vec3 target, \
													t_vec3 up, t_mat4 result);
float			*mat4_scale(float *mat, float scale);
t_mat4			mat4_mult(t_mat4 a, t_mat4 b, t_mat4 result);
t_mat4			mat4_copy(t_mat4 src, t_mat4 dest);

t_mat4			mat4_rotate_model_y(t_mat4 model, float rotate);

t_mat4			mat4_offset(t_vec3 offset, t_mat4 dest);

t_vec3			vec3_get_average(t_vec3 vertices, size_t size, t_vec3 result);

#endif