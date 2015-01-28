/**
 * Skeleton.hpp
 * Contributors:
 *      * Arthur Sonzogni (author)
 * Licence:
 *      * Public Domain
 */
#ifndef SKINNING_T98GXNW7
#define SKINNING_T98GXNW7

#include "Skeleton.hpp"
#include "graphic/Shader.hpp"


class Skinning
{
    struct GL_Vertice
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec4 weight;
        glm::ivec4 boneIndex;
    };

    struct GL_Element
    {
        GLuint v1,v2,v3;
    };

    public:
        Skinning(const std::string& objFileName, Skeleton& skeleton);
        void draw(double time, const glm::mat4& projection, const glm::mat4& view);

    private:
        // data
        Skeleton& skeleton;

        // VBO/VAO/ibo
        GLuint vao,vbo,ibo;

        // shader
        Shader vertexShader;
        Shader fragmentShader;
        ShaderProgram shaderProgram;

        std::vector<GL_Vertice> vertices;
        std::vector<GL_Element> triangles;

        // intern methods
        void readFromFile(const std::string& objFileName);
        void initGL();
        void updateGL();
};

#endif /* end of include guard: SKINNING_T98GXNW7 */
