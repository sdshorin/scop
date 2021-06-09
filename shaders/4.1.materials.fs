
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

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform float time;

void main()
{
    // Окружающая составляющая
    // vec3 ambient = light.ambient * material.ambient;
  	
    // // Диффузная составляющая 
    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // // Отраженная составляющая
    // vec3 viewDir = normalize(viewPos - FragPos);
    // vec3 reflectDir = reflect(-lightDir, norm);  
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * (spec * material.specular);  
        
    // vec3 result = ambient + diffuse + specular;
    //FragColor = vec4( 1.0);
    FragColor.r = cos(time * 1.2);
    FragColor.g = sin(time * 2.0 / 3.0);
    FragColor.b = cos(time * 4.0 / 7.0);
    FragColor.a = 1.0;
    // FragColor = vec4(normalize(FragPos) * , 1.0);
} 

