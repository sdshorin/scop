
#version 410 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vertex_color;  
in vec3 normal;  
in vec3 frag_pos;  
in vec2 uv;  


uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform sampler2D texture_1;
uniform float mix_scale;

void main()
{
    // Окружающая составляющая
    vec3 ambient = light.ambient * material.ambient;
  	
    // // Диффузная составляющая 
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // // Отраженная составляющая
    vec3 view_diw = normalize(viewPos - frag_pos);
    vec3 reflect_dir = reflect(light_dir, norm);  
    float spec = pow(max(dot(view_diw, reflect_dir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    
    // vec2 face_coord = vec2(1-uv.x, uv.y);
	// FragColor = mix(texture(texture1, texCoord), texture(texture2, face_coord), mix_scale);
    if (mix_scale > 0)
	    FragColor = mix(texture(texture_1, uv), vec4(result, 1.0), mix_scale);
    else
        FragColor = vec4(result, 1.0);


    // FragColor = vec4(result, 1.0);
    // FragColor = vec4(vertex_color, 1.0);
} 

