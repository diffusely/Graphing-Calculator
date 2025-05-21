#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

class CameraController
{
public:

	CameraController(float camera_speed, float zoom_speed);
	CameraController();

	~CameraController() = default;

	void processKeyboard(Camera& camera, GLFWwindow* window);
	void processMouseDrag(Camera& camera, GLFWwindow* window);
	void processScroll(Camera& camera, double offset_x, double offset_y);

private:
	float m_camera_speed;
	float m_zoom_speed;

};