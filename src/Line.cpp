#include "Line.h"

Line::Line(glm::vec2 a, glm::vec2 b)
{
	Init(a, b);
}

Line::~Line()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Line::Init(glm::vec2 a, glm::vec2 b)
{
	vertices = { a.x, a.y, b.x, b.y };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Line::Draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);
}
