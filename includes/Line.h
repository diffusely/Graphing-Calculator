#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"

class Line
{
public:

	Line() = default;
	Line(glm::vec2 a, glm::vec2 b);
	Line(glm::vec2 a, glm::vec2 b, glm::vec3 color);
	~Line();

	void Init(glm::vec2 a, glm::vec2 b);
	void Draw(Shader &shader) const;

private:
	GLuint VAO, VBO;
	std::vector<float> vertices;
	glm::vec3 color;
};