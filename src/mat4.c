
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
float *mat4_scale(float *mat, float scale)
{
    mat4_identity(mat);
    mat[0] *= scale;
    mat[5] *= scale;
    mat[10] *= scale;
}


mat4_t mat4_perspective(float h_1, float aspect, float n, float f, float *mat)
{
    mat = mat4_identity(mat);
    mat[15] = 0;
    mat[11] = -1;
    mat[10] = (f + n) / (f - n);
    mat[14] = (-2 * f * n) / (f - n);
    mat[5] = (2 * n) / h_1;
    mat[0] = mat[5] / aspect ;
    return (mat);
}
// void multiply(int mat1[][N], int mat2[][N], int res[][N])
// {
//     int i, j, k;
//     for (i = 0; i < N; i++) {
//         for (j = 0; j < N; j++) {
//             res[i][j] = 0;
//             for (k = 0; k < N; k++)
//                 res[i][j] += mat1[i][k] * mat2[k][j];
//         }
//     }
// }
mat4_t  mat4_mult(mat4_t a, mat4_t b, mat4_t result)
{
    int i;
    int j;
    int k;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            result[i * 4 + j] = 0;
            k = 0;
            while (k < 4)
            {
                result[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
                k++;
            }
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
    mat4_identity(temp1);
    mat4_identity(temp2);
    temp1[3] = pos[0];
    temp1[7] = pos[1];
    temp1[11] = pos[2];
    copy_vec3(x_camera_right, temp2);
    copy_vec3(y_camera_up, temp2 + 4);
    copy_vec3(z_camera_dir, temp2 + 8);
    mat4_mult(temp2, temp1, result);
    return (result);
}


// Пользовательская реализация функции LookAt()
// glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
// {
//     // 1. Position = знаем
//     // 2. Вычисляем cameraDirection
//     glm::vec3 zaxis = glm::normalize(position - target);
//     // 3. Получаем положительный вектор правой оси
//     glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
//     // 4. Вычисляем вектор камеры вверх
//     glm::vec3 yaxis = glm::cross(zaxis, xaxis);
 
//     // Создаем матрицу трансляции и вращения.
//     // В glm мы получаем доступ к элементам как mat[столбец][ряд] из-за расположения столбцов
//     glm::mat4 translation = glm::mat4(1.0f); // единичная матрица по умолчанию
//     translation[3][0] = -position.x; // третий столбец, первый ряд
//     translation[3][1] = -position.y;
//     translation[3][2] = -position.z;
//     glm::mat4 rotation = glm::mat4(1.0f);
//     rotation[0][0] = xaxis.x; // первый столбец, первый ряд
//     rotation[1][0] = xaxis.y;
//     rotation[2][0] = xaxis.z;
//     rotation[0][1] = yaxis.x; // первый столбец, второй ряд
//     rotation[1][1] = yaxis.y;
//     rotation[2][1] = yaxis.z;
//     rotation[0][2] = zaxis.x; // первый столбец, третий ряд
//     rotation[1][2] = zaxis.y;
//     rotation[2][2] = zaxis.z; 
 
//     // Возвращаем LookAt-матрицу как комбинацию матриц трансляции и вращения
//     return rotation * translation; // не забудьте о том, что читать нужно справа налево (сначала трансляция, затем вращение)
// }