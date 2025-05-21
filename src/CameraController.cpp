#include "CameraController.h"

CameraController::CameraController(float camera_speed, float zoom_speed)
	: m_camera_speed(camera_speed), m_zoom_speed(zoom_speed)
{}

CameraController::CameraController()
	: m_camera_speed(0.01f), m_zoom_speed(0.01f)
{}

void CameraController::processKeyboard(Camera &camera, GLFWwindow *window)
{
	float dir = m_camera_speed / camera.getZoom();

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(-dir, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(dir, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(0.0f, dir);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(0.0f, -dir);

}

void CameraController::processMouseDrag(Camera &camera, GLFWwindow *window)
{
	static bool dragging = false;
	static double lastX = 0.0, lastY = 0.0;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		if (!dragging)
		{
			dragging = true;
			lastX = xpos;
			lastY = ypos;
		}
		else
		{
			float dx = static_cast<float>(xpos - lastX);
			float dy = static_cast<float>(ypos - lastY);
			camera.move(-dx * 0.005f, dy * 0.005f);
	
			lastX = xpos;
			lastY = ypos;
		}
	}
	else
	{
		dragging = false;
	}
}

void CameraController::processScroll(Camera &camera, double offset_x, double offset_y)
{
	if (offset_y > 0)
		camera.zoom(1.05f);
	else if (offset_y < 0)
		camera.zoom(0.95f);
}
