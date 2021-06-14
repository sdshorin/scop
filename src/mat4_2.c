#include "scop.h"

t_mat4	mat4_rotation_x(t_mat4 mat, float rotate)
{
	mat4_identity(mat);
	mat[5] = cosf((rotate / 180.0) * PI);
	mat[6] = sinf((rotate / 180.0) * PI);
	mat[9] = -sinf((rotate / 180.0) * PI);
	mat[10] = cosf((rotate / 180.0) * PI);
	return (mat);
}

t_mat4	mat4_rotation_y(t_mat4 mat, float rotate)
{
	mat4_identity(mat);
	mat[0] = cosf((rotate / 180.0) * PI);
	mat[8] = sinf((rotate / 180.0) * PI);
	mat[2] = -sinf((rotate / 180.0) * PI);
	mat[10] = cosf((rotate / 180.0) * PI);
	return (mat);
}

// t_mat4	mat4_rotation_z(t_mat4 mat, float rotate)
// {
// 	mat4_identity(mat);
// 	mat[0] = cosf((rotate / 180.0) * PI);
// 	mat[1] = sinf((rotate / 180.0) * PI);
// 	mat[4] = -sinf((rotate / 180.0) * PI);
// 	mat[5] = cosf((rotate / 180.0) * PI);
// 	return (mat);
// }

t_mat4	mat4_rotate_model_y(t_mat4 model, float rotate)
{
	float	temp1[16];
	float	temp2[16];

	mat4_copy(model, temp2);
	mat4_rotation_y(temp1, rotate);
	mat4_mult(temp1, temp2, model);
	return (model);
}

t_mat4	mat4_perspective(float fov, float aspect, float n, float f)
{
	float	h_1;
	t_mat4	mat;

	h_1 = n * tan(fov * 3.14159265358979323846 / 360.0);
	mat = mat4_identity(0);
	mat[15] = 0;
	mat[11] = -1;
	mat[10] = -(f + n) / (f - n);
	mat[14] = (-2 * f * n) / (f - n);
	mat[5] = (2 * n) / (h_1 * 2);
	mat[0] = mat[5] / aspect ;
	return (mat);
}

t_mat4	mat4_mult(t_mat4 a, t_mat4 b, t_mat4 result)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i * 4 + j] = a[j] * b[i * 4] + \
				a[j + 4] * b[i * 4 + 1] + \
				a[j + 8] * b[i * 4 + 2] + \
				a[j + 12] * b[i * 4 + 3];
			j++;
		}
		i++;
	}
	return (result);
}
