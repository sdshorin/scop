

#include "scop.h"










int ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int read_bmp_data(int fd, t_texture *texture)
{
	if (texture->image_size > 20 * 1024 * 1024 ||
					texture->image_size < texture->height * texture->width * 3)
		return (0);
	if (!(texture->data = (unsigned char*)malloc(texture->image_size)))
		return (0);
	if (read(fd, texture->data, texture->image_size) != texture->image_size)
	{
		free(texture->data);
		texture->data = 0;
		return (0);
	}
	return (1);
}


int parse_bmp_file(int fd, t_texture *texture)
{
	unsigned char header[54];
	int data_pos;

	texture->data = 0;
	if (read(fd, header, 54) != 54 || header[0] != 'B' || header[1] != 'M')
		return (0);
	texture->height = ft_abs(*((int*)&header[0x16]));
	texture->width = ft_abs(*((int*)&header[0x12]));
	texture->image_size = ft_abs(*((int*)&header[0x22]));
	data_pos = ft_abs(*((int*)&header[0x0A]));
	if (data_pos == 0)
		data_pos = 54;
	if (!texture->image_size)
		texture->image_size = texture->height * texture->width * 3;
	while (data_pos > 54)
		if (read(fd, header, ft_min(data_pos - 54, 54)) != ft_min(data_pos - 54, 54))
			return (0);
		else
			data_pos -= ft_min(data_pos - 54, 54);
	return read_bmp_data(fd, texture);
}












