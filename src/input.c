#include "scop.h"

void	process_input_2(GLFWwindow *window, t_env *env, float camera_speed)
{
	float	temp[3];

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		env->camera.pos[0] += env->camera.front[0] * camera_speed;
		env->camera.pos[1] += env->camera.front[1] * camera_speed;
		env->camera.pos[2] += env->camera.front[2] * camera_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		env->camera.pos[0] -= env->camera.front[0] * camera_speed;
		env->camera.pos[1] -= env->camera.front[1] * camera_speed;
		env->camera.pos[2] -= env->camera.front[2] * camera_speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec3_cross(env->camera.front, env->camera.up, temp);
		vec3_norm(temp);
		vec3_scale(temp, camera_speed);
		vec3_minus(env->camera.pos, temp, env->camera.pos);
	}
}

void	process_input_3(GLFWwindow *window, t_env *env, float camera_speed)
{
	float	temp[3];

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec3_cross(env->camera.front, env->camera.up, temp);
		vec3_norm(temp);
		vec3_scale(temp, camera_speed);
		vec3_add(env->camera.pos, temp, env->camera.pos);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		vec3_copy(env->camera.up, temp);
		vec3_scale(temp, camera_speed);
		vec3_add(env->camera.pos, temp, env->camera.pos);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		vec3_copy(env->camera.up, temp);
		vec3_scale(temp, camera_speed);
		vec3_minus(env->camera.pos, temp, env->camera.pos);
	}
}

void	process_input_4(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		env->object->mix_scale += 0.05f;
		if (env->object->mix_scale > 1.0)
			env->object->mix_scale = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		env->object->mix_scale -= 0.05f;
		if (env->object->mix_scale < 0.0)
			env->object->mix_scale = 0.0f;
	}
}

void	process_input(GLFWwindow *window, t_env *env, float delta_time)
{
	float	camera_speed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	camera_speed = 20.0f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera_speed *= 3.0;
	process_input_2(window, env, camera_speed);
	process_input_3(window, env, camera_speed);
	process_input_4(window, env);
}

void	mouse_callback(GLFWwindow *window, double x_pos, double y_pos)
{
	t_camera_look	*look;
	float			x_offset;
	float			y_offset;
	float			temp[3];

	if (!window)
		return ;
	look = get_camera_look();
	if (!look->is_inited)
		init_camera_look(look, x_pos, y_pos);
	x_offset = x_pos - look->last_x;
	y_offset = -y_pos + look->last_y;
	look->last_x = x_pos;
	look->last_y = y_pos;
	look->yaw += x_offset * CAMERA_SENSITIVITY;
	look->pitch += y_offset * CAMERA_SENSITIVITY;
	if (look->pitch > 89.0f)
		look->pitch = 89.0f;
	if (look->pitch < -89.0f)
		look->pitch = -89.0f;
	set_vec3(cos(look->yaw * PI / 180) * cos(look->pitch * PI / 180), \
			sin(look->pitch * PI / 180), \
			sin(look->yaw * PI / 180) * cos(look->pitch * PI / 180), temp);
	vec3_norm(temp);
	vec3_copy(temp, look->camera->front);
}
