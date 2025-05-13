#include "Graph.h"

Graph::Graph(int witdth, int height)
	: window(nullptr)
	, shader(nullptr)
	, width(witdth)
	, height(height)
{
	if (!InitGLFW())
		throw std::runtime_error("GLFW init error");
	if (!InitGLAD())
		throw std::runtime_error("GLAD init error");
	
	this->shader = std::make_unique<Shader>(
		std::string("shaders/vertex.glsl"),
		std::string("shaders/fragment.glsl")
	);

	line_x = std::make_unique<Line>(glm::vec2{-1.0f, 0.0f}, glm::vec2{1.0f, 0.0f});
	line_y = std::make_unique<Line>(glm::vec2{0.0f, -1.0f}, glm::vec2{0.0f, 1.0f});
}

Graph::~Graph()
{
	shader.reset();
	line_x.reset();
	line_y.reset();
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Graph::InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Graph", nullptr, nullptr);
	if (!window)
		return false;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
		glViewport(0, 0, w, h);
	});

	return true;
}

bool Graph::InitGLAD()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Graph::Update()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	shader->Use();
}

void Graph::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	line_x->Draw();
	line_y->Draw();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Graph::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		Update();
		Render();
	}
}