#include "scop.h"

void	exit_error(char *error)
{
	ft_putendl(error);
	exit(1);
}

void	processInput(GLFWwindow *window, t_env *env, float delta_time)
{
	float	temp[3];
	float	cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	cameraSpeed = 20.0f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed *= 3.0;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		env->camera.pos[0] += env->camera.front[0] * cameraSpeed;
		env->camera.pos[1] += env->camera.front[1] * cameraSpeed;
		env->camera.pos[2] += env->camera.front[2] * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		env->camera.pos[0] -= env->camera.front[0] * cameraSpeed;
		env->camera.pos[1] -= env->camera.front[1] * cameraSpeed;
		env->camera.pos[2] -= env->camera.front[2] * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec3_cross(env->camera.front, env->camera.up, temp);
		vec3_norm(temp);
		vec3_scale(temp, cameraSpeed);
		vec3_minus(env->camera.pos, temp, env->camera.pos);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec3_cross(env->camera.front, env->camera.up, temp);
		vec3_norm(temp);
		vec3_scale(temp, cameraSpeed);
		vec3_add(env->camera.pos, temp, env->camera.pos);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		vec3_copy(env->camera.up, temp);
		vec3_scale(temp, cameraSpeed);
		vec3_add(env->camera.pos, temp, env->camera.pos);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		vec3_copy(env->camera.up, temp);
		vec3_scale(temp, cameraSpeed);
		vec3_minus(env->camera.pos, temp, env->camera.pos);
	}
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

void	load_obj_to_gpu(t_env *env)
{
	glGenVertexArrays(1, &env->buffs.vao);
	glGenBuffers(1, &env->buffs.vbo);
	glGenBuffers(1, &env->buffs.cbo);
	glGenBuffers(1, &env->buffs.uvbo);
	if (env->with_light)
		glGenBuffers(1, &env->buffs.nbo);
	if (env->texture.data)
	{
		glGenTextures(1, &env->buffs.texture);
		glBindTexture(GL_TEXTURE_2D, env->buffs.texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, env->texture.width, \
		env->texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, env->texture.data);
	}
	glBindVertexArray(env->buffs.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffs.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * \
			env->object->vert_buffer.size, env->object->vert_buffer.data, \
			GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), \
																(void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffs.cbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * \
		env->object->colors_buffer.size, env->object->colors_buffer.data, \
														GL_STATIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffs.uvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * env->object->uv_buffer.size, \
							env->object->uv_buffer.data, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), \
																(void *)0);
	glEnableVertexAttribArray(2);
	if (env->with_light)
	{
		glBindBuffer(GL_ARRAY_BUFFER, env->buffs.nbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * \
			env->object->normals_buffer.size, env->object->normals_buffer.data, \
											GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), \
															(void *)0);
		glEnableVertexAttribArray(3);
	}
}

GLint	get_l(int shader, char *name)
{
	return (glGetUniformLocation(shader, name));
}

void	start_main_loop(t_env *env)
{
	float	temp[3];
	float	delta_time;
	float	last_frame;

	glUseProgram(env->shader);
	if (env->with_light)
	{
		temp[0] = -30.2f;
		temp[1] = -1.5f;
		temp[2] = 1.5f;
		glUniform3f(get_l(env->shader, "light.position"), \
											temp[0], temp[1], temp[2]);
		glUniform3f(get_l(env->shader, "viewPos"), \
				env->camera.pos[0], env->camera.pos[1], env->camera.pos[2]);
		glUniform3f(get_l(env->shader, "light.ambient"), 0.2f, 0.1f, 0.31f);
		glUniform3f(get_l(env->shader, "light.diffuse"), 1.0f, 0.9f, 0.91f);
		glUniform3f(get_l(env->shader, "light.specular"), 0.5f, 0.5f, 0.5f);
		glUniform3f(get_l(env->shader, "material.ambient"), 0.2f, 0.1f, 0.31f);
		glUniform3f(get_l(env->shader, "material.diffuse"), 1.0f, 0.9f, 0.31f);
		glUniform3f(get_l(env->shader, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(get_l(env->shader, "material.shininess"), 32.0f);
	}
	if (env->texture.data)
		glUniform1i(glGetUniformLocation(env->shader, "texture_1"), 0);
	glUniform1f(glGetUniformLocation(env->shader, "mix_scale"), 0.0);
	glUniformMatrix4fv(get_l(env->shader, "projection"), 1, GL_FALSE, \
														env->camera.proj);
	glUniformMatrix4fv(get_l(env->shader, "model"), 1, GL_FALSE, \
													env->object->model);
	check_error(3);
	while (!glfwWindowShouldClose(env->window))
	{
		usleep(20000);
		float current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;
		processInput(env->window, env, delta_time);
		glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(env->shader);
		glBindVertexArray(env->buffs.vao);
		mat4_create_camera_matrix(env->camera.pos, vec3_add(env->camera.pos, \
					env->camera.front, temp), env->camera.up, env->camera.view);
		mat4_rotate_model_y(env->object->model, 0.1f);
		glUniformMatrix4fv(glGetUniformLocation(env->shader, "model"), 1, \
												 GL_FALSE, env->object->model);
		glUniformMatrix4fv(glGetUniformLocation(env->shader, "view"), 1, \
													GL_FALSE, env->camera.view);
		if (env->texture.data)
			glUniform1f(glGetUniformLocation(env->shader, "mix_scale"), \
														env->object->mix_scale);
		glDrawArrays(GL_TRIANGLES, 0, env->object->vert_buffer.size / 3);
		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
}

int	is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	open_file(char *path, int error_exit)
{
	int		fd;

	if (!is_regular_file(path))
	{
		ft_putendl("It isn't file!");
		if (error_exit)
			exit(0);
		else
			return (-1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		ft_putendl("Cannot open file!");
		if (error_exit)
			exit(0);
		else
			return (-1);
	}
	return (fd);
}

void	free_memory(t_env *env)
{
	glDeleteVertexArrays(1, &env->buffs.vao);
	glDeleteBuffers(1, &env->buffs.vbo);
	glDeleteBuffers(1, &env->buffs.cbo);
	glDeleteBuffers(1, &env->buffs.uvbo);
	if (env->with_light)
		glDeleteBuffers(1, &env->buffs.nbo);
	if (env->texture.data)
	{
		glDeleteTextures(1, &env->buffs.texture);
		free(env->texture.data);
	}
	glDeleteProgram(env->shader);
	glfwDestroyWindow(env->window);
	glfwTerminate();
	free(env->camera.proj);
	ft_float_vector_free(&env->object->verticles);
	ft_float_vector_free(&env->object->uv);
	ft_float_vector_free(&env->object->normals);
	ft_float_vector_free(&env->object->vert_buffer);
	ft_float_vector_free(&env->object->uv_buffer);
	ft_float_vector_free(&env->object->normals_buffer);
	ft_float_vector_free(&env->object->colors_buffer);
	free(env->object);
}

void	check_error(int i)
{
	if (glGetError())
	{
		ft_putnbr(i);
		ft_putendl(" line - Opengl ERROR!");
	}
}

int	main(int argc, char **argv)
{
	t_env	env;
	int		fd;

	if (argc == 2)
		env.object = create_object_from_file(open_file(argv[1], 1));
	else
		exit_error("USAGE: ./command file");
	fd = open_file(TEXTURE_PATH, 1);
	if (fd < 0 || !parse_bmp_file(fd, &env.texture))
		exit_error("Error: can't open bmp file");
	env.with_light = !!env.object->normals_buffer.size;
	init_app(&env);
	init_positions(&env);
	check_error(1);
	if (env.with_light)
		env.shader = create_shader(VERTEX_SHADER, FRAGMENT_SHADER);
	else
		env.shader = create_shader(VERTEX_SHADER_NO_LIGHT, \
									FRAGMENT_SHADER_NO_LIGHT);
	load_obj_to_gpu(&env);
	check_error(2);
	start_main_loop(&env);
	free_memory(&env);
}
