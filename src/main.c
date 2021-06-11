
#include "scop.h"
#include <fcntl.h>
#include <sys/stat.h>

# define  CHECK_ERROR() check_error(__LINE__);



float vertices[] = {
     // координаты      
     0.5f,  0.5f, 1.0f,    // верхняя правая
     0.5f, -0.5f, 1.0f,    // нижняя правая
    -0.5f, -0.5f, 0.0f,   // нижняя левая
    -0.5f,  0.5f, 0.0f,  // верхняя левая 
};

unsigned int indices[] = {
        0, 1, 3, // первый треугольник
        1, 2, 3  // второй треугольник
    };






void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// printf("%s\n", "frame changed");
}

void print_view_status(t_env *env)
{
	printf("\ncamera_pos:( %f, %f, %f)\n", env->camera.pos[0], env->camera.pos[1], env->camera.pos[2]);
	printf("pamera_front:( %f, %f, %f)\n", env->camera.front[0], env->camera.front[1], env->camera.front[2]);
	printf("pamera_up:( %f, %f, %f)\n", env->camera.up[0], env->camera.up[1], env->camera.up[2]);
	print_matrix("view", env->camera.view);
}

void processInput(GLFWwindow *window, t_env *env, float delta_time)
{
	float temp[3];
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
}


t_camera_look *get_camera_look()
{
	static t_camera_look data;

	return (&data);
}

void init_camera_look(t_camera_look *look, double x_pos, double y_pos)
{
	look->is_inited = 1;	
	look->last_x = x_pos;
	look->last_y = y_pos;
	look->pitch = 0.0f;
	look->yaw = -90.0f;
}

void mouse_callback(GLFWwindow* window, double x_pos, double y_pos)
{
	t_camera_look *look;
	float x_offset;
	float y_offset;
	float temp[3];

	look = get_camera_look();
	if (!look->is_inited)
		init_camera_look(look, x_pos, y_pos);
	x_offset = x_pos - look->last_x;
	y_offset = -y_pos + look->last_y ; // перевернуто, так как диапазон y-координаты определяется снизу вверх
	look->last_x = x_pos;
	look->last_y = y_pos;
	look->yaw   += x_offset * CAMERA_SENSITIVITY;
	look->pitch   += y_offset * CAMERA_SENSITIVITY;
	if(look->pitch > 89.0f)
		look->pitch =  89.0f;
	if(look->pitch < -89.0f)
		look->pitch = -89.0f;
	set_vec3(cos(look->yaw *PI/180) * cos(look->pitch *PI/180),
			sin(look->pitch * PI/180),
			sin(look->yaw *PI/180) * cos(look->pitch *PI/180), temp);
	vec3_norm(temp);
	vec3_copy(temp, look->camera->front);
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
	env->camera.look = get_camera_look();
	env->camera.look->camera = &env->camera;
	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(env->window, mouse_callback);
	// glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(env->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
}

void init_positions(t_env *env)
{
	float temp[3];
	set_vec3(0.0f, 0.0f, 1.0f, env->camera.pos);
	// set_vec3(0.0f, 0.0f, 3.0f, env->camera.pos);
	set_vec3(0.0f, 0.0f, -1.0f, env->camera.front);
	vec3_add(env->camera.pos, env->camera.front, temp);
	set_vec3(0.0f, 1.0f, 0.0f, env->camera.up);
	mat4_perspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f, env->camera.proj);
	mat4_create_camera_matrix(env->camera.pos, temp, env->camera.up, env->camera.view);
	print_matrix("view", env->camera.view);
	print_matrix("proj", env->camera.proj);
	// exit(0);
}

void load_obj_to_gpu(t_env *env)
{
	glGenVertexArrays(1, &env->buffs.vao);
	glGenBuffers(1, &env->buffs.vbo);
	glGenBuffers(1, &env->buffs.ebo);

	glBindVertexArray(env->buffs.vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->buffs.vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * env->object->verticles.size, env->object->verticles.data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->buffs.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * env->object->triangels.size, env->object->triangels.data, GL_STATIC_DRAW);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	print_matrix("proj------", env->camera.proj);
	glUniformMatrix4fv(glGetUniformLocation(env->shader, "model"), 1, GL_FALSE, env->object->model);
	check_error(3);
	while(!glfwWindowShouldClose(env->window))
	{
		CHECK_ERROR()
		usleep(20000);
		// printf(" 1ERROR!  %d\n", glGetError());
		float current_time = glfwGetTime();
		delta_time = current_time - last_frame;
		last_frame = current_time;
		// printf("%f  %f\n", current_time, delta_time);
		glUniformMatrix4fv(glGetUniformLocation(env->shader, "view"), 1, GL_FALSE, env->camera.view);
		glUniform1f(glGetUniformLocation(env->shader, "time"), current_time);
		// printf(" 2ERROR!  %d\n", glGetError());
		processInput(env->window, env, delta_time);
		glClearColor(0.2f, 0.9f, 0.3f, 1.0f);
		// printf(" 3ERROR!  %d\n", glGetError());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(env->shader);
		// printf(" 4ERROR!  %d\n", glGetError());
		glBindVertexArray(env->buffs.vao); // ?????
		// printf(" 45ERROR!  %d\n", glGetError());
		mat4_create_camera_matrix(env->camera.pos, vec3_add(env->camera.pos, env->camera.front, temp), env->camera.up, env->camera.view);
		//print_view_status(env);
		// printf(" 5ERROR!  %d\n", glGetError());
		CHECK_ERROR()

		// float camX = sin(glfwGetTime()) * 4.0f;
		// float camZ = cos(glfwGetTime())  * 4.0f;
		// set_vec3(camX, 0.0, camZ, env->camera.pos);
		// set_vec3(2.0, 2.0, 0.0, temp);
		// set_vec3(0.0, 1.0, 0.0, up);
		// mat4_create_camera_matrix(env->camera.pos, temp, up, env->camera.view);



		// glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, offsset);
		glUniformMatrix4fv(glGetUniformLocation(env->shader, "view"), 1, GL_FALSE, env->camera.view);
		CHECK_ERROR()
			
		glDrawElements(GL_TRIANGLES, env->object->triangels.size, GL_UNSIGNED_INT, 0);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(env->window);
		CHECK_ERROR()
		glfwPollEvents();
		CHECK_ERROR()
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
		printf("Line %d ERROR!", i);
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
	mat4_scale(env.object->model, 0.2);
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
