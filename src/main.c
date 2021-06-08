
#include "scop.h"
#include <fcntl.h>
#include <sys/stat.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// printf("%s\n", "frame changed");
}


void processInput(GLFWwindow *window, t_env *env, float delta_time)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	
	// if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	// {
	// 	mix_scale += 0.05f;
	// 	if (mix_scale > 1.0)
	// 		mix_scale = 1.0f;
	// }
	// if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	// {
	// 	mix_scale -= 0.05f;
	// 	if (mix_scale < 0.0f)
	// 		mix_scale = 0.0f;
	// }


    const float cameraSpeed = 5.0f * delta_time; // настройте по вашему усмотрению
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			env->camera.pos[0] += env->camera.front[0] * cameraSpeed;
			env->camera.pos[1] += env->camera.front[1] * cameraSpeed;
			env->camera.pos[2] += env->camera.front[2] * cameraSpeed;
			// vec3_t temp_v =  vec3_create(camera_front);
			// vec3_scale(temp_v, cameraSpeed, 0);
			// vec3_add(camera_pos, temp_v, 0);
			// free(temp_v);
		}
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			// vec3_t temp_v =  vec3_create(camera_front);
			// vec3_scale(temp_v, cameraSpeed, 0);
			// vec3_subtract(camera_pos, temp_v, 0);
			// free(temp_v);
			env->camera.pos[0] -= env->camera.front[0] * cameraSpeed;
			env->camera.pos[1] -= env->camera.front[1] * cameraSpeed;
			env->camera.pos[2] -= env->camera.front[2] * cameraSpeed;
		}
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	// 	{
    //     	// camera_pos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	// 		vec3_t temp_v =  vec3_create(camera_front);
	// 		vec3_cross(camera_front, camera_up, temp_v);
	// 		vec3_normalize(temp_v, 0);
	// 		vec3_scale(temp_v, cameraSpeed, 0);
	// 		vec3_subtract(camera_pos, temp_v, 0);
	// 		free(temp_v);
	// 		printf("%s\n", "GLFW_KEY_A");
	// 	}
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	// 	{
    //     	// camera_pos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	// 		vec3_t temp_v =  vec3_create(camera_front);
	// 		vec3_cross(camera_front, camera_up, temp_v);
	// 		vec3_normalize(temp_v, 0);
	// 		vec3_scale(temp_v, cameraSpeed, 0);
	// 		vec3_add(camera_pos, temp_v, 0);
	// 		free(temp_v);
	// 		printf("%s\n", "GLFW_KEY_D");
	// 	}
	// if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	// 	{
    //     	// camera_pos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	// 		mat4_t temp_m = mat4_identity(0);
	// 		mat4_rotate(temp_m, 0.01f, camera_up, 0);
	// 		mat4_multiplyVec4(temp_m, camera_front, 0);
	// 		free(temp_m);
	// 		// vec3_t temp_v =  vec3_create(camera_front);
	// 		// vec3_cross(camera_front, camera_up, temp_v);
	// 		// vec3_normalize(temp_v, 0);
	// 		// vec3_scale(temp_v, cameraSpeed, 0);
	// 		// vec3_add(camera_pos, temp_v, 0);
	// 		// free(temp_v);
	// 		// printf("%s\n", "GLFW_KEY_D");
	// 	}
	// if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	// 	{
    //     	// camera_pos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	// 		mat4_t temp_m = mat4_identity(0);
	// 		mat4_rotate(temp_m, -0.01f, camera_up, 0);
	// 		mat4_multiplyVec4(temp_m, camera_front, 0);
	// 		free(temp_m);
	// 		// vec3_t temp_v =  vec3_create(camera_front);
	// 		// vec3_cross(camera_front, camera_up, temp_v);
	// 		// vec3_normalize(temp_v, 0);
	// 		// vec3_scale(temp_v, cameraSpeed, 0);
	// 		// vec3_add(camera_pos, temp_v, 0);
	// 		// free(temp_v);
	// 		// printf("%s\n", "GLFW_KEY_D");
	// 	}

}


void print_matrix(char *name, float *mat)
{
	int row, columns;
	printf("mat %s:\n", name);
	for (row=0; row<4; row++)
	{
		for(columns=0; columns<4; columns++)
		{
			printf("%f     ", mat[row * 4 + columns]);
		}
		printf("\n");
	}
}

void init_app(t_env *env)
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
	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glfwSetCursorPosCallback(window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void init_positions(t_env *env)
{
	float temp[3];
	set_vec3(0.0f, 0.0f, 3.0f, env->camera.pos);
	// set_vec3(0.0f, 0.0f, 3.0f, env->camera.pos);
	set_vec3(0.0f, 0.0f, -1.0f, env->camera.front);
	vec3_add(env->camera.pos, env->camera.front, temp);
	set_vec3(0.0f, 1.0f, 0.0f, env->camera.up);
	mat4_perspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f, env->camera.proj);
	mat4_create_camera_matrix(env->camera.pos, temp, env->camera.up, env->camera.view);
	print_matrix("view", env->camera.view);
	print_matrix("proj", env->camera.proj);
}

void load_obj_to_gpu(t_env *env)
{
	glGenVertexArrays(1, &env->buffs.vao);
	glGenBuffers(1, &env->buffs.vbo);
	glGenBuffers(1, &env->buffs.ebo);

	glBindVertexArray(env->buffs.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffs.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * env->object->verticles.size, env->object->verticles.data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->buffs.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * env->object->triangels.size, env->object->triangels.data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);
}


void start_main_loop(t_env *env)
{
	float temp[3];
	float up[3];
	float delta_time;
	float last_frame;
	
	glUseProgram(env->shader);
	glUniformMatrix4fv(glGetUniformLocation(env->shader, "projection"), 1, GL_FALSE, env->camera.proj);
	glUniformMatrix4fv(glGetUniformLocation(env->shader, "model"), 1, GL_FALSE, env->object->model);
	check_error(3);
	while(!glfwWindowShouldClose(env->window))
	{
		check_error(4);
		usleep(20000);
		float current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;
		// printf("%f  %f\n", current_time, delta_time);

		processInput(env->window, env, delta_time);
		glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(env->shader);
		glBindVertexArray(env->buffs.vao); // ?????
		mat4_create_camera_matrix(env->camera.pos, vec3_add(env->camera.pos, env->camera.front, temp), env->camera.up, env->camera.view);
		check_error(5);

		// float camX = sin(glfwGetTime()) * 10.0f;
		// float camZ = cos(glfwGetTime())  * 10.0f;
		// set_vec3(camX, 2.0, camZ, env->camera.pos);
		// set_vec3(2.0, 2.0, 0.0, temp);
		// set_vec3(0.0, 1.0, 0.0, up);
		// mat4_create_camera_matrix(env->camera.pos, temp, up, env->camera.view);



		// glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, offsset);
		glUniformMatrix4fv(glGetUniformLocation(env->shader, "view"), 1, GL_FALSE, env->camera.view);
		check_error(6);
			
		glDrawElements(GL_TRIANGLES, env->object->triangels.size, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(env->window);
		check_error(7);
		glfwPollEvents();
		check_error(8);
	}
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
	glDeleteProgram(env->shader);
	// Delete all!
}

int current_path(int i) {
   char cwd[200];
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("%d Current working dir: %s\n", i, cwd);
   } else {
       perror("getcwd() error");
       return 1;
   }
   return 0;
}

void check_error(int i)
{
	if (glGetError())
		printf("%d ERROR!  %d", i, glGetError());
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
	mat4_scale(env.object->model, 0.3);
	// check_error(0);
	init_app(&env);
	init_positions(&env);
	check_error(1);
	env.shader = create_shader(VERTEX_SHADER, FRAGMENT_SHADER);
	
	load_obj_to_gpu(&env);
	check_error(2);
	start_main_loop(&env);
	free_memory(&env);
}
