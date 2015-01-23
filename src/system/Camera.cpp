#include "Camera.hpp"
#include "Input.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define THETA_MAX -5*2*M_PI/360
#define THETA_MIN -170*2*M_PI/360
#define R_MIN 0.1

float Camera::THETA_MULTIPLIER = 0.01;
float Camera::PHI_MULTIPLIER = 0.01;
float Camera::ZOOM_MULTIPLIER = 1;
float Camera::TRANSLATION_MULTIPLIER = 0.5;

Camera::Camera()
{
	this->r = 10;
	this->theta = -90;
	this->phi = 0;
	this->target = glm::vec3(0.0,0.0,0.0);
}

void Camera::update(float deltaTime)
{
    if (Input::isKeyHold(GLFW_KEY_TAB)) return;
	// Manage rotation
	if(Input::isMouseHold(GLFW_MOUSE_BUTTON_LEFT))
	{
		this->theta -= Input::deltaY() * Camera::THETA_MULTIPLIER;
		if(this->theta > THETA_MAX) this->theta = THETA_MAX;
		if(this->theta < THETA_MIN) this->theta = THETA_MIN;
		this->phi += Input::deltaX() * Camera::PHI_MULTIPLIER;
	}
	// Manage translation
	else if(Input::isMouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		this->target += glm::vec3(
				-Input::deltaX()*cos(phi), 
				-Input::deltaY(), 
				Input::deltaX()*sin(phi)
				)*Camera::TRANSLATION_MULTIPLIER;
	}


	// Manage zoom
	if(Input::isKeyHold(GLFW_KEY_KP_ADD) || Input::isKeyHold(GLFW_KEY_LEFT_SHIFT))
	{
		this->r -= 100.0*Camera::ZOOM_MULTIPLIER * deltaTime;
	}
	if(Input::isKeyHold(GLFW_KEY_KP_SUBTRACT) || Input::isKeyHold(GLFW_KEY_LEFT_CONTROL))
	{
		this->r += 100.0*Camera::ZOOM_MULTIPLIER * deltaTime;
	}
	if(this->r < R_MIN) this->r = R_MIN;
}

glm::mat4 Camera::lookAt()
{
	return glm::lookAt(
			glm::vec3(r*sin(phi)*sin(theta), r*cos(theta), r*cos(phi)*sin(theta))+target,
			target,
			glm::vec3(0.0, 1.0, 0.0));
}

void Camera::setTarget(glm::vec3 target)
{
	this->target = target;
}

void Camera::setTheta(float theta)
{
	this->theta = theta;
	if(this->theta > THETA_MAX) this->theta = THETA_MAX;
	if(this->theta < THETA_MIN) this->theta = THETA_MIN;
}

void Camera::setPhi(float phi)
{
	this->phi = phi;
}

void Camera::setR(float r)
{
	this->r = r;
}
