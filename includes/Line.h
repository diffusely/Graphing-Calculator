#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>


class Line
{
public:

	Line() = default;
	Line(glm::vec2 a, glm::vec2 b);
	~Line();

	void Init(glm::vec2 a, glm::vec2 b);
	void Draw() const;

private:
	GLuint VAO, VBO;	
	std::vector<float> vertices;
};