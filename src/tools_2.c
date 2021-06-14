#include "scop.h"

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
