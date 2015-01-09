#version 150

in vec3 position;

uniform mat4 projection;
uniform mat4 view;

void main(void)
{
    gl_Position = projection * view * vec4(position,1.0); 
};
