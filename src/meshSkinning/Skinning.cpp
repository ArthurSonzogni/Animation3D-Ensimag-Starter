#include "Skinning.hpp"
#include <iostream>
#include "utils/glError.hpp"
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include <algorithm>


Skinning::Skinning(const std::string& objFileName, Skeleton& skeleton):
    skeleton(skeleton),
    vertexShader("shader/skinning.vert",GL_VERTEX_SHADER),
    fragmentShader("shader/skinning.frag",GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader,fragmentShader})
{
    readFromFile(objFileName);
    initGL();
}


struct FaceIndex { GLuint v[9]; };
void Skinning::readFromFile(const std::string& objFileName)
{
    std::ifstream file;

    // file open
    file.open(objFileName.c_str());
    if (not file.is_open())
        throw std::invalid_argument("The file " + objFileName + " doesn't exist");

    std::vector<glm::vec3> vertexObj;
    std::vector<glm::vec3> normalsObj;
    std::vector<glm::vec2> textureObj;

    std::vector<FaceIndex> facesObj;

    // file parsing
    std::string identifier;
    while(file>>identifier)
    {
        if (identifier=="v")
        {
            double x,y,z;
            file>>x>>y>>z;
            vertexObj.push_back(glm::vec3(x,y,z));
        }
        else if (identifier=="vn")
        {
            double x,y,z;
            file>>x>>y>>z;
            normalsObj.push_back(glm::vec3(x,y,z));
        }
        else if (identifier=="vt")
        {
            double x,y;
            file>>x>>y;
            textureObj.push_back(glm::vec2(x,1.f-y));
        }
        else if (identifier=="f")
        {
            getline(file,identifier);
            setlocale(LC_ALL, "en_US.utf8");
            FaceIndex f;
            sscanf(identifier.c_str(),"%d/%d/%d %d/%d/%d %d/%d/%d",
                    &f.v[0],
                    &f.v[1],
                    &f.v[2],
                    &f.v[3],
                    &f.v[4],
                    &f.v[5],
                    &f.v[6],
                    &f.v[7],
                    &f.v[8]
                  );
            for(int i=0;i<9;++i)
                f.v[i]--;
            facesObj.push_back(f);
        }
    }

    // construction des vertex
    vertices.resize(vertexObj.size());
    triangles.resize(facesObj.size());

    for(size_t i = 0; i < vertexObj.size();++i)
    {
        vertices[i].position = vertexObj[i];
        vertices[i].weight = glm::vec4(0.25);
        vertices[i].boneIndex = glm::ivec4(0,1,2,3);
    }
    for(size_t i=0;i< facesObj.size();++i)
    {

        triangles[i].v1 = facesObj[i].v[0];
        triangles[i].v2 = facesObj[i].v[3];
        triangles[i].v3 = facesObj[i].v[6];

        vertices[triangles[i].v1].texCoord = textureObj[facesObj[i].v[1]];
        vertices[triangles[i].v2].texCoord = textureObj[facesObj[i].v[4]];
        vertices[triangles[i].v3].texCoord = textureObj[facesObj[i].v[7]];

        vertices[triangles[i].v1].normal = normalsObj[facesObj[i].v[2]];
        vertices[triangles[i].v2].normal = normalsObj[facesObj[i].v[5]];
        vertices[triangles[i].v3].normal = normalsObj[facesObj[i].v[8]];

    }


    file.close();

    std::cout << "vertice Number = " << vertices.size() << std::endl;
    std::cout << "element Number = " << triangles.size() << std::endl;

    // compute weight and boneIndex
    std::cout << "Computing weight ..." << std::flush;
    for(size_t i = 0; i < vertices.size();++i)
    {
        PointWeight w;
        skeleton.getWeight(w, vertices[i].position);
        vertices[i].weight = w.weight;
        vertices[i].boneIndex = w.index;
    }
    std::cout << "Done" << std::endl;

}


void Skinning::initGL()
{
    // vbo
    glGenBuffers( 1, &vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GL_Vertice), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(GL_Element), triangles.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // vao
    glGenVertexArrays( 1, &vao);
    glBindVertexArray(vao);


        // bind vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // map vbo to shader attributes
        shaderProgram.setAttribute("position", 3, sizeof(GL_Vertice), offsetof(GL_Vertice, position));
        shaderProgram.setAttribute("normal",   3, sizeof(GL_Vertice), offsetof(GL_Vertice, normal));
        shaderProgram.setAttribute("texCoord", 2, sizeof(GL_Vertice), offsetof(GL_Vertice, texCoord));
        shaderProgram.setAttribute("weight",   4, sizeof(GL_Vertice), offsetof(GL_Vertice, weight));
        shaderProgram.setAttribute("boneIndex",4, sizeof(GL_Vertice), offsetof(GL_Vertice, boneIndex));


        // bind the ibo
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    // vao end
    glBindVertexArray(0);

}
void Skinning::updateGL()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Skinning::GL_Vertice), &vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Skinning::draw(double time, const glm::mat4& projection, const glm::mat4& view)
{
    int frame = skeleton.getFrameMirror(time);

    std::vector<glm::mat4> bones;
    skeleton.getTransformation(frame,bones);
    bones.resize(50);

    
    shaderProgram.use();    

        glUniformMatrix4fv( shaderProgram.uniform("bones"), bones.size() , false, glm::value_ptr(bones[0]));


        // send uniforms
        shaderProgram.setUniform("projection",projection);
        shaderProgram.setUniform("view",view);

        glCheckError(__FILE__,__LINE__);

        glBindVertexArray(vao);

        
        glCheckError(__FILE__,__LINE__);
            glDrawElements(
                 GL_TRIANGLES,      // mode
                 triangles.size() * 3,         // count
                 GL_UNSIGNED_INT,   // type
                 NULL               // element array buffer offset
             );

        glBindVertexArray(0);

    shaderProgram.unuse();
}
