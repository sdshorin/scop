#version 410 core
layout (location = 0) in vec3 pos;
layout (location = 1) in float color;
layout (location = 2) in vec2 uv_in;
layout (location = 3) in vec3 norm_in;
out vec3 vertex_color;
out vec3 normal;
out vec3 frag_pos;
out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    frag_pos = vec3(model * vec4(pos, 1.0));
    normal = mat3(transpose(inverse(model))) * norm_in;  
    gl_Position = projection * view * model * vec4(pos, 1.0);
    vertex_color = vec3(color);
    uv = uv_in;
}

