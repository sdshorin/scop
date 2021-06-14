#include "scop.h"

t_mat4	mat4_identity(float *dest)
{
	if (!dest)
		dest = malloc(sizeof(float) * 16);
	if (!dest)
		exit(1);
	dest[0] = 1;
	dest[1] = 0;
	dest[2] = 0;
	dest[3] = 0;
	dest[4] = 0;
	dest[5] = 1;
	dest[6] = 0;
	dest[7] = 0;
	dest[8] = 0;
	dest[9] = 0;
	dest[10] = 1;
	dest[11] = 0;
	dest[12] = 0;
	dest[13] = 0;
	dest[14] = 0;
	dest[15] = 1;
	return (dest);
}

t_mat4	mat4_scale(t_mat4 mat, float scale)
{
	mat4_identity(mat);
	mat[0] *= scale;
	mat[5] *= scale;
	mat[10] *= scale;
	return (mat);
}

t_mat4	mat4_offset(t_vec3 offset, t_mat4 dest)
{
	mat4_identity(dest);
	dest[12] = offset[0];
	dest[13] = offset[1];
	dest[14] = offset[2];
	return (dest);
}

t_mat4	mat4_copy(t_mat4 src, t_mat4 dest)
{
	ft_memcpy(dest, src, sizeof(float) * 16);
	return (dest);
}

t_mat4	mat4_create_camera_matrix(t_vec3 pos, t_vec3 target,
										t_vec3 up, t_mat4 result)
{
	float	z_camera_dir[3];
	float	x_camera_right[3];
	float	y_camera_up[3];

	vec3_norm(vec3_minus(pos, target, z_camera_dir));
	vec3_norm(vec3_cross(vec3_norm(up), z_camera_dir, x_camera_right));
	vec3_cross(z_camera_dir, x_camera_right, y_camera_up);
	mat4_identity(result);
	result[12] = -(x_camera_right[0] * pos[0] + x_camera_right[1] * pos[1] + \
										x_camera_right[2] * pos[2]);
	result[13] = -(y_camera_up[0] * pos[0] + y_camera_up[1] * pos[1] + \
											y_camera_up[2] * pos[2]);
	result[14] = -(z_camera_dir[0] * pos[0] + z_camera_dir[1] * pos[1] + \
											z_camera_dir[2] * pos[2]);
	copy_vec3_with_offset(x_camera_right, result, 4);
	copy_vec3_with_offset(y_camera_up, result + 1, 4);
	copy_vec3_with_offset(z_camera_dir, result + 2, 4);
	return (result);
}
