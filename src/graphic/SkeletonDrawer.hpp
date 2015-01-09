#ifndef SKELETONDRAWER_KJAU1JB
#define SKELETONDRAWER_KJAU1JB

#include "graphic/Shader.hpp"
#include "meshSkinning/Skeleton.hpp"

class SkeletonDrawer
{
    public:
        SkeletonDrawer(Skeleton& skeleton);
        ~SkeletonDrawer();

        void draw(float time, const glm::mat4& projection, const glm::mat4& view);

    private:
        Skeleton& skeleton;

        void init();
        void free();
        
        
        // opengl 
        GLuint  vao,vbo;

        // shader
        Shader vertexShader;
        Shader fragmentShader;
        ShaderProgram shaderProgram;

        // data
        int nbPoints;
        int nbFrame;
};

#endif /* end of include guard: SKELETONDRAWER_KJAU1JB */
