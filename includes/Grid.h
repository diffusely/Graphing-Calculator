#pragma once

#include "Line.h"
#include "Camera.h"

#include <vector>
#include <memory>

class Grid
{
public:

	Grid(int, int, int);
	~Grid();

	void draw(Shader &shader);
	void update(Camera &camera);
	void clear();


	void initGrid();

private:
	int m_size;
	int m_width;
	int m_height;

	std::vector<std::unique_ptr<Line>> m_grid_lines;
};