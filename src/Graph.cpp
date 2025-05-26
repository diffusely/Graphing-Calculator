#include "Graph.h"

#include "../lib/imgui/imgui.h"
#include "../lib/imgui/backends/imgui_impl_glfw.h"
#include "../lib/imgui/backends/imgui_impl_opengl3.h"

Graph::Graph(int width, int height, std::string input)
	: window(nullptr)
	, shader(nullptr)
	, width(width)
	, height(height)
	, input(input)
	, m_grid(width, height, 20)
{
	
	if (!InitGLFW())
		throw std::runtime_error("GLFW init error");
	if (!InitGLAD())
		throw std::runtime_error("GLAD init error");
	
	this->shader = std::make_unique<Shader>(
		std::string("shaders/vertex.glsl"),
		std::string("shaders/fragment.glsl")
	);


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	DrawFunc(input);
}

Graph::~Graph()
{
	shader.reset();
	func.clear();
	m_grid.clear();


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Graph::ScrollCallback(GLFWwindow* window, double offset_x, double offset_y)
{
	Graph* self = static_cast<Graph*>(glfwGetWindowUserPointer(window));
	if (self)
		self->m_controller.processScroll(self->m_camera, offset_x, offset_y);
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


void Graph::Update()
{


	
	PressKey();
	m_grid.update(m_camera);
	//UpdateMouse();
}

void Graph::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	float aspect = float(height) / width;
	float scale = m_camera.getZoom();

	glm::mat4 projection = glm::ortho(
		-1.0f * scale, 1.0f * scale,
		-1.0f * scale * aspect, 1.0f * scale * aspect
	);

	glm::vec2 cameraPos{m_camera.getOffsetX(), m_camera.getOffsetY()};
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraPos, 0.0f));

	shader->SetMat4("projection", projection);
	shader->SetMat4("view", view);

	DrawFunc(input);

	shader->Use();
	m_grid.draw(*shader);
	for (const auto& it : func)
		it->Draw(*shader);

}

void Graph::PressKey()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	m_controller.processKeyboard(m_camera, window);
	//m_controller.processMouseDrag(m_camera, window);

}

void Graph::UpdateMouse()
{
	glm::vec2 mousePos = GetMousePosition();
	std::cout << "Mouse pos: " << mousePos.x << ", " << mousePos.y << std::endl;
}

void Graph::DrawFunc(const std::string &input)
{
	func.clear();

	ExpTree tree(input);

	float aspect = float(width) / height;
	float left = m_camera.getOffsetX() - m_camera.getZoom();
	float right = m_camera.getOffsetY() + m_camera.getZoom();

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
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Graph Controller");

        ImGui::InputText("Function", functionInput, IM_ARRAYSIZE(functionInput));

        if (ImGui::Button("Update Function")) {
            input = std::string(functionInput);
            DrawFunc(input);
        }

        ImGui::Text("Current function: %s", input.c_str());

        ImGui::End();

        Update();

        Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}