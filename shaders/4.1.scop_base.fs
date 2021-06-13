
#version 410 core
out vec4 FragColor;



in vec3 vertex_color;  
in vec3 uv;  



void main()
{
 
    // vec2 face_coord = vec2(1-uv.x, uv.y);
	// FragColor = mix(texture(texture1, texCoord), texture(texture2, face_coord), mix_scale);


    FragColor = vec4(vertex_color, 1.0);
    // FragColor = vec4(vertex_color, 1.0);
} 

