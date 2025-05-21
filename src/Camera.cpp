#include "Camera.h"
#include <glad/glad.h>


Camera::Camera(float x, float y, float zoom)
	: m_offset_x(x), m_offset_y(y), m_zoom(zoom) {}	

Camera::Camera()
	: m_offset_x(0), m_offset_y(0), m_zoom(1.0f) {}

void Camera::transform()
{
	glScalef(m_zoom, m_zoom, 1.0f); // Z -> scale 1.0f
	glTranslatef(m_offset_x, m_offset_y, 0.0f); // Z -> point 0.0f
}

void Camera::move(float dx, float dy)
{
	m_offset_x += dx;
	m_offset_y += dy;
}

void Camera::zoom(float factor)
{
	m_zoom *= factor;

	if (m_zoom <= 0.1f ) m_zoom = 0.1f;
	else if (m_zoom >= 50.0f) m_zoom = 50.0f;
}

float Camera::getOffsetX() const { return m_offset_x; }
float Camera::getOffsetY() const { return m_offset_y; }
float Camera::getZoom() const { return m_zoom; }