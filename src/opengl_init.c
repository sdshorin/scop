#include "scop.h"

void	load_texture_to_gpu(t_env *env)
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

void	load_buffers_to_gpu(t_env *env)
{
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
		load_texture_to_gpu(env);
	glBindVertexArray(env->buffs.vao);
	load_buffers_to_gpu(env);
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

void	init_light_shader(t_env *env)
{
	float	temp[3];

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

void	init_uniforms(t_env *env)
{
	glUniform1f(glGetUniformLocation(env->shader, "mix_scale"), 0.0);
	glUniformMatrix4fv(get_l(env->shader, "projection"), 1, GL_FALSE, \
														env->camera.proj);
	glUniformMatrix4fv(get_l(env->shader, "model"), 1, GL_FALSE, \
													env->object->model);
}
