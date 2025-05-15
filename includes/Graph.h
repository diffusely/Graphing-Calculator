#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Line.h"
#include "ExpTree.h"

#include <memory>
#include <iostream>
#include <exception>
#include <vector>

#include <mutex>
#include <atomic>

class Graph
{
public:
	glm::vec2 cameraPos = glm::vec2(0.0f, 0.0f);
	float cameraSpeed = 0.02f;

	float zoom = 1.0f;
	float zoomSpeed = 0.1f;

public:
	Graph(int witdth, int height, std::string input);
	~Graph();

	void DrawFunc(const std::string &);
	glm::vec2 GetMousePosition() const;
	void Run();

private:
	GLFWwindow* window;
	std::unique_ptr<Shader> shader;

	int width;
	int height;

private:
	std::vector<std::unique_ptr<Line>> grid_lines;
	std::vector<std::unique_ptr<Line>> func;

private:
	// Update and Render
	void Update();
	void Render();

	void PressKey();
	void UpdateMouse();

private:
	// Init
	bool InitGLFW();
	bool InitGLAD();
	void InitGrid();
};