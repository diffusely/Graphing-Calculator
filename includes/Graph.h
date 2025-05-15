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

#include <mutex>
#include <atomic>

class Graph
{
public:
	std::mutex formula_mutex;
	std::string input_formula = "x^2";
	std::atomic<bool> has_new_formula = true;
	std::atomic<bool> running = true;
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

private:
	// Init
	bool InitGLFW();
	bool InitGLAD();
	void InitGrid();
};