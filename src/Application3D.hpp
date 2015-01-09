#ifndef APPLICATION3D_9YCQ0OVR
#define APPLICATION3D_9YCQ0OVR

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "system/Application.hpp"
#include "graphic/Shader.hpp"
#include "meshSkinning/Skeleton.hpp"
#include "graphic/SkeletonDrawer.hpp"
#include "meshSkinning/Skinning.hpp"
#include "system/Input.hpp"
#include "system/Camera.hpp"

class Application3D : public Application
{
    public:
        Application3D();

    protected:
        virtual void loop();

    private:
        float time;

        // shader
        Shader vertexShader;
        Shader fragmentShader;
        ShaderProgram shaderProgram;

        // shader matrix uniform
        glm::mat4 projection;
        glm::mat4 view;

        // VBO/VAO/ibo
        GLuint vao,vbo,ibo;

        // skeleton
        Skeleton skeleton;
        SkeletonDrawer skeletonDrawer;

        // skinning
        Skinning skinning;

		// Camera
		Camera *camera;
        
};

#endif /* end of include guard: APPLICATION3D_9YCQ0OVR */
