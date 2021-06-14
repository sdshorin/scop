
#include "scop.h"




mat4_t mat4_identity(float *dest) {
	if (!dest)
		if (!(dest = malloc(sizeof(float) * 16)))
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
    return dest;
}
mat4_t mat4_scale(mat4_t mat, float scale)
{
    mat4_identity(mat);
    mat[0] *= scale;
    mat[5] *= scale;
    mat[10] *= scale;
    return (mat);
}

mat4_t mat4_offset(vec3_t offset, mat4_t dest)
{
    mat4_identity(dest);
    dest[12] = offset[0];
    dest[13] = offset[1];
    dest[14] = offset[2];
    return (dest);
}

mat4_t mat4_copy(mat4_t src, mat4_t dest)
{
    ft_memcpy(dest, src, sizeof(float) * 16);
    return (dest);
}


mat4_t mat4_rotation_x(mat4_t mat, float rotate)
{
    mat4_identity(mat);
    mat[5] = cosf((rotate / 180.0) * PI);
    mat[6] = sinf((rotate / 180.0) * PI);
    mat[9] = -sinf((rotate / 180.0) * PI);
    mat[10] = cosf((rotate / 180.0) * PI);
    return (mat);
}

mat4_t mat4_rotation_y(mat4_t mat, float rotate)
{
    mat4_identity(mat);
    mat[0] = cosf((rotate / 180.0) * PI);
    mat[8] = sinf((rotate / 180.0) * PI);
    mat[2] = -sinf((rotate / 180.0) * PI);
    mat[10] = cosf((rotate / 180.0) * PI);
    return (mat);
}

mat4_t mat4_rotation_z(mat4_t mat, float rotate)
{
    mat4_identity(mat);
    mat[0] = cosf((rotate / 180.0) * PI);
    mat[1] = sinf((rotate / 180.0) * PI);
    mat[4] = -sinf((rotate / 180.0) * PI);
    mat[5] = cosf((rotate / 180.0) * PI);
    return (mat);
}

mat4_t mat4_rotate_model_y(mat4_t model, float rotate)
{
    float temp1[16];
    float temp2[16];

    mat4_copy(model, temp2);
    mat4_rotation_y(temp1, rotate);
    mat4_mult(temp1, temp2, model);
    return (model);
}


mat4_t mat4_perspective(float fov, float aspect, float n, float f, float *mat)
{
    float   h_1;
    h_1 = n * tan(fov * 3.14159265358979323846 / 360.0);

    mat = mat4_identity(mat);
    mat[15] = 0;
    mat[11] = -1;
    mat[10] = -(f + n) / (f - n);
    mat[14] = (-2 * f * n) / (f - n);
    mat[5] = (2 * n) / (h_1 * 2);
    mat[0] = mat[5] / aspect ;
    return (mat);
}


mat4_t  mat4_mult(mat4_t a, mat4_t b, mat4_t result)
{
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            result[i * 4 + j] = a[j] * b[i * 4]
                                + a[j + 4] * b[i * 4 + 1]
                                + a[j + 8] * b[i * 4 + 2]
                                + a[j + 12] *b[i * 4 + 3];
            j++;
        }
        i++;
    }
    return (result);
}



mat4_t mat4_create_camera_matrix(vec3_t pos, vec3_t target, vec3_t up, mat4_t result)
{
    float z_camera_dir[3];
    float x_camera_right[3];
    float y_camera_up[3];
    float temp1[15];
    float temp2[15];

    vec3_norm(vec3_minus(pos, target, z_camera_dir));
    vec3_norm(vec3_cross(vec3_norm(up), z_camera_dir, x_camera_right));
    vec3_cross(z_camera_dir, x_camera_right, y_camera_up);
    mat4_identity(result);
    result[12] = -(x_camera_right[0] * pos[0] + x_camera_right[1] * pos[1] + x_camera_right[2] * pos[2]);
    result[13] = -(y_camera_up[0] * pos[0] + y_camera_up[1] * pos[1] + y_camera_up[2] * pos[2]);
    result[14] = -(z_camera_dir[0] * pos[0] + z_camera_dir[1] * pos[1] + z_camera_dir[2] * pos[2]);
    copy_vec3_with_offset(x_camera_right, result, 4);
    copy_vec3_with_offset(y_camera_up, result + 1, 4);
    copy_vec3_with_offset(z_camera_dir, result + 2, 4);
    return (result);
}
