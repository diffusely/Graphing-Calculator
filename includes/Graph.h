#pragma once

#include <memory>
#include <iostream>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Line.h"

class Graph
{
private:
	// Update and Render
	void Update();
	void Render();

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
	std::unique_ptr<Line> line_x;
	std::unique_ptr<Line> line_y;

private:
	// Init
	bool InitGLFW();
	bool InitGLAD();
};