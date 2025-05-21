#include "Graph.h"

Graph::Graph(int witdth, int height, std::string input)
	: window(nullptr)
	, shader(nullptr)
	, width(witdth)
	, height(height)
	, input(input)
{
	
	if (!InitGLFW())
		throw std::runtime_error("GLFW init error");
	if (!InitGLAD())
		throw std::runtime_error("GLAD init error");
	
	this->shader = std::make_unique<Shader>(
		std::string("shaders/vertex.glsl"),
		std::string("shaders/fragment.glsl")
	);

	DrawFunc(input);
	InitGrid();
}

Graph::~Graph()
{
	shader.reset();
	grid_lines.clear();
	func.clear();
	glfwDestroyWindow(window);
	glfwTerminate();
}

static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Graph* graph = static_cast<Graph*>(glfwGetWindowUserPointer(window));
    graph->zoom -= graph->zoomSpeed * float(yoffset) * graph->zoom;
    if (graph->zoom < 0.01f) graph->zoom = 0.01f;
    if (graph->zoom > 100.0f) graph->zoom = 100.0f;
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

	glfwSetWindowUserPointer(window, this);
	glfwSetScrollCallback(window, ScrollCallback);

	return true;
}

bool Graph::InitGLAD()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Graph::InitGrid()
{
	grid_lines.clear();

	for(float i = -0.05f; i > -1.0; i-= 0.05f)
		this->grid_lines.push_back(std::make_unique<Line>(glm::vec2{i, -1.0f}, glm::vec2{i, 1.0f}));
	for(float i = 0.05f; i < 1.0; i+= 0.05f)
		this->grid_lines.push_back(std::make_unique<Line>(glm::vec2{i, -1.0f}, glm::vec2{i, 1.0f}));
	for(float i = 0.0f; i > -1.0; i-= 0.05f * width / height)
		this->grid_lines.push_back(std::make_unique<Line>(glm::vec2{-1.0f, i}, glm::vec2{1.0f, i}));
	for(float i = 0.05f * width / height; i < 1.0; i+= 0.05f * width / height)
		this->grid_lines.push_back(std::make_unique<Line>(glm::vec2{-1.0f, i}, glm::vec2{1.0f, i}));

	this->grid_lines.push_back(std::make_unique<Line>(glm::vec2{-1.0f, 0.0f}
		, glm::vec2{1.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}));
	this->grid_lines.push_back(std::make_unique<Line>(glm::vec2{0.0f, -1.0f}
		, glm::vec2{0.0f, 1.0f}, glm::vec3{1.0f, 1.0f, 1.0f}));
}

void Graph::Update()
{
	
	PressKey();
	UpdateGrid();
	UpdateMouse();
}

void Graph::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float aspect = float(height) / width;
	float scale = zoom;

	glm::mat4 projection = glm::ortho(
		-1.0f * scale, 1.0f * scale,
		-1.0f * scale * aspect, 1.0f * scale * aspect
	);

	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPos, 0.0f));

	shader->SetMat4("projection", projection);
	shader->SetMat4("view", view);

	DrawFunc(input);

	shader->Use();
	for (const auto& it : grid_lines)
		it->Draw(*shader);
	for (const auto& it : func)
		it->Draw(*shader);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Graph::PressKey()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos.x -= cameraSpeed1 * zoom;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos.x += cameraSpeed1 * zoom;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos.y += cameraSpeed1 * zoom;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos.y -= cameraSpeed1 * zoom;

	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) 
		zoom -= zoomSpeed * zoom;
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		zoom += zoomSpeed * zoom;
	

	std::cout << cameraPos.x << std::endl;
	if (zoom < 0.01f) zoom = 0.01f;
	if (zoom > 100.0f) zoom = 100.0f;

	std::cout << zoom << "\n";
}

void Graph::UpdateMouse()
{
	glm::vec2 mousePos = GetMousePosition();
	std::cout << "Mouse pos: " << mousePos.x << ", " << mousePos.y << std::endl;
}

void Graph::UpdateGrid()
{
	grid_lines.clear();

	float aspect = float(height) / width;
	float left = cameraPos.x - zoom;
	float right = cameraPos.x + zoom;
	float bottom = cameraPos.y - zoom * aspect;
	float top = cameraPos.y + zoom * aspect;
	
	const float pixelsPerGridLine = 30.0f;
	float visibleWorldWidth = 2.0f * zoom;
	float worldUnitsPerPixel = visibleWorldWidth / float(width);
	float gridStep = pixelsPerGridLine * worldUnitsPerPixel;
	
	float startX = std::floor(left / gridStep) * gridStep;
	float startY = std::floor(bottom / gridStep) * gridStep;
	
	for (float x = startX; x <= right; x += gridStep)
		grid_lines.push_back(std::make_unique<Line>(glm::vec2{x, bottom}, glm::vec2{x, top}));
	
	for (float y = startY; y <= top; y += gridStep)
		grid_lines.push_back(std::make_unique<Line>(glm::vec2{left, y}, glm::vec2{right, y}));
	
	grid_lines.push_back(std::make_unique<Line>(
		glm::vec2{left, 0.0f},
		glm::vec2{right, 0.0f},
		glm::vec3{1.0f, 1.0f, 1.0f}
	));
	
	grid_lines.push_back(std::make_unique<Line>(
		glm::vec2{0.0f, bottom},
		glm::vec2{0.0f, top},
		glm::vec3{1.0f, 1.0f, 1.0f}
	));
	
}

void Graph::DrawFunc(const std::string &input)
{
	func.clear();

	ExpTree tree(input);

	float aspect = float(width) / height;
	float left = cameraPos.x - zoom;
	float right = cameraPos.x + zoom;

	float prev_x = left;
	float prev_y = tree.getResult(tree.getRoot(), prev_x) / aspect;

	const float MAX_DELTA_Y = 100.f;

	for (float x = prev_x + 0.01f; x <= right; x += 0.01f)
	{
		float y = tree.getResult(tree.getRoot(), x) / aspect;

		if (!std::isfinite(y) || !std::isfinite(prev_y) || std::abs(y - prev_y) > MAX_DELTA_Y)
		{
			prev_x = x;
			prev_y = y;
			continue;
		}

		func.push_back(std::make_unique<Line>(
			glm::vec2{prev_x, prev_y},
			glm::vec2{x, y},
			glm::vec3{1.0f, 0.0f, 0.0f}
		));

		prev_x = x;
		prev_y = y;
	}
	
}

glm::vec2 Graph::GetMousePosition() const
{
	double xpos, ypos;
	glfwGetCursorPos(this->window, &xpos, &ypos);


	float normX = static_cast<float>(xpos / width  * 2.0 - 1.0);
	float normY = static_cast<float>((height - ypos) / height * 2.0 - 1.0);

	return glm::vec2(normX, normY);
}

void Graph::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		Update();
		Render();
	}
}