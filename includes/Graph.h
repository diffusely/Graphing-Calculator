#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Line.h"
#include "ExpTree.h"
#include "Camera.h"
#include "CameraController.h"
#include "Grid.h"

#include <memory>
#include <iostream>
#include <exception>
#include <vector>

#include <mutex>
#include <atomic>

class Graph
{
public:
	Graph(int witdth, int height, std::string input);
	~Graph();

	void DrawFunc(const std::string &);
	glm::vec2 GetMousePosition() const;
	static void ScrollCallback(GLFWwindow* window, double offset_x, double offset_y);
	void Run();

private:
	Camera m_camera;
	CameraController m_controller;
	Grid m_grid;

private:
	GLFWwindow* window;
	std::unique_ptr<Shader> shader;

	int width;
	int height;

private:

	std::vector<std::unique_ptr<Line>> func;
	std::string input;
private:
	// Update and Render
	void Update();
	void Render();

	void PressKey();
	void UpdateMouse();
	void UpdateGrid();

private:
	// Init
	bool InitGLFW();
	bool InitGLAD();
	void InitGrid();
};