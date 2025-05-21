#include "Grid.h"

Grid::Grid(int width, int height, int size)
	: m_width(width)
	, m_height(height)
	, m_size(size)
{
	m_grid_lines.reserve(20);
}

Grid::~Grid()
{

}

void Grid::clear()
{
	m_grid_lines.clear();
}

void Grid::draw(Shader &shader)
{
	for (const auto& it : m_grid_lines)
		it->Draw(shader);
}

void Grid::update(Camera &camera)
{
	m_grid_lines.clear();

	float x = camera.getOffsetX();
	float y = camera.getOffsetY();
	float zoom = camera.getZoom();

	float aspect = float(m_height) / m_width;
	float left = x - zoom;
	float right = x + zoom;
	float bottom = y - zoom * aspect;
	float top = y + zoom * aspect;
	
	float visibleWorldWidth = 2.0f * zoom;
	float worldUnitsPerPixel = visibleWorldWidth / float(m_width);
	float gridStep = m_size * worldUnitsPerPixel;
	
	float startX = std::floor(left / gridStep) * gridStep;
	float startY = std::floor(bottom / gridStep) * gridStep;
	
	for (float x = startX; x <= right; x += gridStep)
		m_grid_lines.push_back(std::make_unique<Line>(glm::vec2{x, bottom}, glm::vec2{x, top}));
	
	for (float y = startY; y <= top; y += gridStep)
		m_grid_lines.push_back(std::make_unique<Line>(glm::vec2{left, y}, glm::vec2{right, y}));
	
	m_grid_lines.push_back(std::make_unique<Line>(
		glm::vec2{left, 0.0f},
		glm::vec2{right, 0.0f},
		glm::vec3{1.0f, 1.0f, 1.0f}
	));
	
	m_grid_lines.push_back(std::make_unique<Line>(
		glm::vec2{0.0f, bottom},
		glm::vec2{0.0f, top},
		glm::vec3{1.0f, 1.0f, 1.0f}
	));
}
