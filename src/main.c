/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:03:32 by kpsylock          #+#    #+#             */
/*   Updated: 2021/05/10 13:21:19 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <fcntl.h>
 #include <sys/stat.h>


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
	// init_app(env);
	// start_main_loop(env);
	// free_memory(); ?
}
