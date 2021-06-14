#include "scop.h"

void check_shader_compile(unsigned int shader, char *path)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", path, infoLog);
		exit(1);
	} 
}




unsigned int create_shader_part(char *path_vertex, int type)
{
	char vertexShaderSource[1024*8];
	int fd = open(path_vertex, O_RDONLY);
	int readed = 0;
	const char *s;
	unsigned int vertexShader;
	if (fd < 0 || (readed = read(fd, vertexShaderSource, 1024*8 - 1)) == (1024*8 - 1))
	{
		printf("%s\n", "Cannot open file!");
		exit(0);
	}
	vertexShaderSource[readed] = '\0';
	vertexShader = glCreateShader(type);
	s = vertexShaderSource;
	glShaderSource(vertexShader, 1, &s, NULL);
	glCompileShader(vertexShader);
	check_shader_compile(vertexShader, path_vertex);
	return (vertexShader);
}



unsigned int create_shader(char *path_vertex, char* path_fragment)
{
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;
	GLint			success;
	char infoLog[512];

	vertexShader = create_shader_part(path_vertex, GL_VERTEX_SHADER);
	fragmentShader = create_shader_part(path_fragment, GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", path_vertex, infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); 
	return shaderProgram;
}