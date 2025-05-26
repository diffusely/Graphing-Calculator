
#include "../lib/imgui/imgui.h"
#include "../lib/imgui/backends/imgui_impl_glfw.h"
#include "../lib/imgui/backends/imgui_impl_opengl3.h"

// Minimal example: ImGui + OpenGL + GLFW
// Use this to connect input text + button and change your function string.

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "imgui.h"

// Dummy function to simulate updating the graph
void updateGraphWithFunction(const std::string& func) {
    std::cout << "Graph function updated to: " << func << std::endl;
    // TODO: add your parser and OpenGL update logic here
}

int main(int, char**)
{
    // Setup GLFW
    if (!glfwInit())
        return -1;

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui OpenGL Graph Example", NULL, NULL);
    if (window == NULL)
        return -1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup ImGui context


    // Setup ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Variables
    char functionInput[128] = "sin(x)";
    std::string currentFunction = "sin(x)";

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // ImGui window
        ImGui::Begin("Graph Controller");

        ImGui::InputText("Function", functionInput, IM_ARRAYSIZE(functionInput));

        if (ImGui::Button("Update Function")) {
            currentFunction = std::string(functionInput);
            updateGraphWithFunction(currentFunction);
        }

        ImGui::Text("Current function: %s", currentFunction.c_str());

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

