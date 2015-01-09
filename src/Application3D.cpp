#include "Application3D.hpp"
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils/glError.hpp"
#include "system/Input.hpp"



Application3D::Application3D():
    Application(),
    vertexShader("shader/shader.vert",GL_VERTEX_SHADER),
    fragmentShader("shader/shader.frag",GL_FRAGMENT_SHADER),
    shaderProgram({vertexShader,fragmentShader}),
    skeleton("data/run.bvh"),
    skeletonDrawer(skeleton),
    skinning("data/human.obj",skeleton),
	camera(NULL)
{
	camera = new Camera();
	camera->setTarget(glm::vec3(0.0, 20.0, 0.0));
	camera->setR(140.f);
	camera->setPhi(4.f);
    glCheckError(__FILE__,__LINE__);
}



void Application3D::loop()
{
    float t = getTime();
    // set matrix
    projection = glm::perspective(float(2.0*atan(getHeight()/1920.f)), getWindowRatio(), 0.1f, 1000.f);

	Input::update(getWindow());
	if(Input::isKeyHold(GLFW_KEY_ESCAPE))
	{
		exit();
	}
	
	camera->update();
	view = camera->lookAt();

    // clear
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skeletonDrawer.draw(t,projection,view);
    skinning.draw(t,projection,view);
}
