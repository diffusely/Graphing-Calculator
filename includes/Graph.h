#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Line.h"

#include <memory>
#include <iostream>
#include <exception>
#include <vector>

class Graph
{
public:
	Graph(int witdth, int height);
	~Graph();

	void Run();

private:
	GLFWwindow* window;
	std::unique_ptr<Shader> shader;

	int width;
	int height;

private:
	std::vector<std::unique_ptr<Line>> grid_lines;

private:
	// Update and Render
	void Update();
	void Render();

private:
	// Init
	bool InitGLFW();
	bool InitGLAD();
	void InitGrid();
};