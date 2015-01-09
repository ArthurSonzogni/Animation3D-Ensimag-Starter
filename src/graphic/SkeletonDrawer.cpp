#include "SkeletonDrawer.hpp"
#include <iostream>
#include "utils/glError.hpp"


SkeletonDrawer::SkeletonDrawer(Skeleton& skeleton):
    skeleton(skeleton),
    vertexShader("shader/wireframe.vert",GL_VERTEX_SHADER),
    fragmentShader("shader/wireframe.frag",GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader,fragmentShader})
{
    init();
}

SkeletonDrawer::~SkeletonDrawer()
{
    free();
}

void SkeletonDrawer::init()
{
    ////////////////////////////
    //
    // creation of the vertex array buffer
    //
    ////////////////////////////

    std::vector<glm::vec3> data;

    skeleton.getWireframe(0,data);
    nbPoints = data.size() - 2 ;

    // vbo
    glGenBuffers( 1, &vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, nbPoints * sizeof(glm::vec3), &data[2], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vao
    glGenVertexArrays( 1, &vao);
    glBindVertexArray(vao);

        // bind vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // map vbo to shader attributes
        shaderProgram.setAttribute("position", 3, sizeof(glm::vec3),0);

    // vao end
    glBindVertexArray(0);
    
}

void SkeletonDrawer::free()
{
    std::cout << "TODO : SkeletonDrawer::free()" << std::endl;
}

void SkeletonDrawer::draw(float time, const glm::mat4& projection, const glm::mat4& view)
{
    int frame = skeleton.getFrameMirror(time);

    // load the wireframe
    std::vector<glm::vec3> data;
    skeleton.getWireframe(frame,data);

    // send data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, nbPoints * sizeof(glm::vec3), &data[2]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shaderProgram.use();    

        // send uniforms
        shaderProgram.setUniform("projection",projection);
        shaderProgram.setUniform("view",view);


        glBindVertexArray(vao);
        
            glDrawArrays(
                 GL_LINES,      // mode
                 0,            // offset
                 nbPoints     // count
             );

        glBindVertexArray(0);


    shaderProgram.unuse();
}
