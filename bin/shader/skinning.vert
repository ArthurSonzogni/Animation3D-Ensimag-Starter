#version 150

/*glm::vec3 position;*/
/*glm::vec3 normal;*/
/*glm::vec2 texCoord;*/
/*glm::vec4 weight;*/
/*glm::ivec4 boneIndex;*/

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in vec4 weight;
in ivec4 boneIndex;

uniform mat4 projection = mat4(1.0);
uniform mat4 view = mat4(1.0);

uniform mat4 bones[50];

uniform vec4 lightPosition = vec4(0.0,1.0,0.2,0.0);

out vec4 fPosition;
out vec2 fTexCoord;
out vec4 fLightPosition;
out vec3 fNormal;

void main(void)
{
    mat4 transformation = mat4(1.0);
    
    fPosition = view * transformation * vec4(position,1.0);
    fLightPosition = view * lightPosition;

    fTexCoord = texCoord;
    fNormal = vec3(view * vec4(normal,0.0));

    gl_Position = projection * fPosition;
}
