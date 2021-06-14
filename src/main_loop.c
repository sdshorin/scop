#include "scop.h"

GLint	get_l(int shader, char *name)
{
	return (glGetUniformLocation(shader, name));
}

void	update_uniforms(t_env *env)
{
	float	temp[3];

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
}

void	step(t_env *env, float *delta_time, float *last_frame)
{
	float	current_time;

	current_time = glfwGetTime();
	*delta_time = current_time - *last_frame;
	*last_frame = current_time;
	process_input(env->window, env, *delta_time);
	glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(env->shader);
	glBindVertexArray(env->buffs.vao);
	update_uniforms(env);
	glDrawArrays(GL_TRIANGLES, 0, env->object->vert_buffer.size / 3);
	glfwSwapBuffers(env->window);
	glfwPollEvents();
}

void	start_main_loop(t_env *env)
{
	float	delta_time;
	float	last_frame;

	glUseProgram(env->shader);
	if (env->with_light)
		init_light_shader(env);
	if (env->texture.data)
		glUniform1i(glGetUniformLocation(env->shader, "texture_1"), 0);
	init_uniforms(env);
	while (!glfwWindowShouldClose(env->window))
	{
		usleep(20000);
		step(env, &delta_time, &last_frame);
	}
}
