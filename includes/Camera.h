#pragma once

#include <iostream>

class Camera
{
public:

	Camera(float, float, float);
	Camera();
	~Camera();

	// Functions
	void transform();
	void move(float, float);
	void zoom(float);

	// Get
	float getOffsetX() const;
	float getOffsetY() const;
	float getZoom() const;

private:
	float m_offset_x;
	float m_offset_y;
	float m_zoom;
};