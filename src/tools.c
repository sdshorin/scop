#include "scop.h"

void	exit_error(char *error)
{
	ft_putendl(error);
	exit(1);
}

t_camera_look	*get_camera_look(void)
{
	static t_camera_look	data;

	return (&data);
}

void	init_camera_look(t_camera_look *look, double x_pos, double y_pos)
{
	look->is_inited = 1;
	look->last_x = x_pos;
	look->last_y = y_pos;
	look->pitch = 0.0f;
	look->yaw = -90.0f;
}

void	init_app(t_env *env)
{
	if (!glfwInit())
		exit(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	env->window = glfwCreateWindow(800, 600, "scop", NULL, NULL);
	if (env->window == NULL)
	{
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(env->window);
	env->camera.look = get_camera_look();
	env->camera.look->camera = &env->camera;
	glfwSetCursorPosCallback(env->window, mouse_callback);
	glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void	init_positions(t_env *env)
{
	float	temp[3];

	set_vec3(0.0f, 0.0f, 3.0f, env->camera.pos);
	set_vec3(0.0f, 0.0f, -1.0f, env->camera.front);
	vec3_add(env->camera.pos, env->camera.front, temp);
	set_vec3(0.0f, 1.0f, 0.0f, env->camera.up);
	env->camera.proj = mat4_perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
	mat4_create_camera_matrix(env->camera.pos, temp, env->camera.up, \
													env->camera.view);
	mat4_offset(vec3_neg(vec3_get_average(env->object->verticles.data, \
				env->object->verticles.size / 3, temp)), env->object->model);
}
