
#include "scop.h"

typedef float vec3_t[3];
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