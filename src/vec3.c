
#include "scop.h"


// typedef struct s_vec3 { float x[3]; } t_vec3;


vec3_t vec3(float a, float b, float c) {
    vec3_t dest = malloc(sizeof(float) * 3);

    dest[0] = a;
    dest[1] = b;
    dest[2] = c;
 
    return dest;
}

vec3_t set_vec3(float a, float b, float c, float *dest)
{
    dest[0] = a;
    dest[1] = b;
    dest[2] = c;
 
    return dest;
}

vec3_t copy_vec3_with_offset(float *src, float *dest, int offset)
{
    dest[0] = src[0];
    dest[offset] = src[1];
    dest[2 * offset] = src[2];
    return dest;
}

vec3_t  vec3_add(vec3_t a, vec3_t b, vec3_t dest)
{
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return (dest);
}

vec3_t vec3_copy(vec3_t source, vec3_t dest)
{
    dest[0] = source[0];
    dest[1] = source[1];
    dest[2] = source[2];
    return (dest);
}

vec3_t  vec3_minus(vec3_t a, vec3_t b, vec3_t dest)
{
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
    dest[2] = a[2] - b[2];
    return (dest);
}

vec3_t  vec3_norm(vec3_t vec)
{
    float sum;

    sum = vec[0] + vec[1] + vec[2];
    sum = vec[0] * vec[0] + vec[1] * vec[1]+ vec[2] * vec[2];
    if (sum == 0.0)
        return (vec);
    sum = sqrt(sum);
    vec[0] /= sum;
    vec[1] /= sum;
    vec[2] /= sum;
    return (vec);
}

vec3_t vec3_scale(vec3_t vec, float scale)
{
    vec[0] = vec[0] * scale;
    vec[1] = vec[1] * scale;
    vec[2] = vec[2] * scale;
    return (vec);
}

vec3_t  vec3_cross(vec3_t a, vec3_t b, vec3_t dest)
{
    dest[0] = a[1] * b[2] - a[2] * b[1];
    dest[1] = a[2] * b[0] - a[0] * b[2];
    dest[2] = a[0] * b[1] - a[1] * b[0];
    return (dest);
}