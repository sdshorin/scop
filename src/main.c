/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:03:32 by kpsylock          #+#    #+#             */
/*   Updated: 2021/05/15 13:55:02 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <fcntl.h>
#include <sys/stat.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	printf("%s\n", "frame changed");
}




void init_app(t_env *env)
{
	if (!glfwInit())
        exit(1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "scop", NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void init_positions(t_env *env)
{
	set_vec3(0.0f, 0.0f, 3.0f, env->camera.pos);
	set_vec3(0.0f, 0.0f, 1.0f, env->camera.front);
	set_vec3(0.0f, 1.0f, 0.0f env->camera.up);
	mat4_identity(env->camera.view);
	mat4_t proj = mat4_perspective((float)fov, (800.0f + mix_scale)/600.0f, 0.1f, 100.0f, 0);
	
}

void load_obj_to_gpu(t_env *env)
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);


	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	printf("Maximum nr of vertex attributes supported: %d\n", nrAttributes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
}


void start_main_loop(t_env *env)
{
	while(!glfwWindowShouldClose(window))
	{
		usleep(20000);
		float current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;
		// printf("%f  %f\n", current_time, delta_time);

		processInput(window);
		glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		mat4_lookAt(camera_pos, vec3_add(camera_pos, camera_front, temp), camera_up, view);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, offsset);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, view);
			
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	glfwSwapBuffers(window);
		glfwPollEvents();
}







int		is_regular_file(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int		open_file(char *path)
{
	int		fd;

	if (!is_regular_file(path))
	{
		ft_putendl("First arg isn't file!");
		exit(0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		ft_putendl("Cannot open file specified in first arg!");
		exit(1);
	}
	return fd;
}

void free_memory(t_env *env)
{
	glfwTerminate();
	glDeleteProgram();
	// Delete all!
}


int		main(int argc, char **argv)
{
	t_env	env;
	int		fd;

	if (argc == 2)
	{
		fd = open_file(argv[1]);
		env.object = create_object_from_file(fd);
	}
	else
	{
		ft_putendl("USAGE: ./command file");
		exit(0);
	}
	init_app(&env);
	init_positions(&env)
	env.shader = create_shader(VERTEX_SHADER, FRAGMENT_SHADER);
	
	load_obj_to_gpu(&env);
	start_main_loop(env);
	free_memory();
}
