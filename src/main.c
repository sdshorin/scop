#include "scop.h"

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
	check_error(3);
	free_memory(&env);
}
