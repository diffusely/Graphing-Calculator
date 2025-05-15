#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Line.h"
#include "ExpTree.h"

#include <memory>
#include <iostream>
#include <exception>
#include <vector>

class Graph
{
public:
	Graph(int witdth, int height, std::string input);
	~Graph();

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

	void DrawFunc(const std::string &);

private:
	// Init
	bool InitGLFW();
	bool InitGLAD();
	void InitGrid();
};