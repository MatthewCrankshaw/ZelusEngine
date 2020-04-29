#include "title_bar.h"
#include <GLFW\glfw3.h>

TitleBar::TitleBar(){

    fullscreen = false;
    exitPressed = false;
}

void TitleBar::SetupGLFW(GLFWwindow* window) {
    this->window = window;
}

void TitleBar::CreateTitleBar() {

    ImGuiWindowFlags window_flags = 0;
    
    window_flags |= ImGuiWindowFlags_MenuBar;
    window_flags |= ImGuiWindowFlags_NoResize;

    if (!ImGui::Begin("Zelus Engine", NULL, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    // Most "big" widgets share a common width settings by default.
    //ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);    // Use 2/3 of the space for widgets and 1/3 for labels (default)
    ImGui::PushItemWidth(ImGui::GetFontSize() * - 12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.

    // Menu Bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::MenuItem("Exit Program", NULL, &exitPressed);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Full Screen", NULL, &fullscreen);
            ImGui::MenuItem("Console", NULL, nullptr);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            ImGui::MenuItem("Metrics", NULL, nullptr);
            ImGui::MenuItem("Style Editor", NULL, nullptr);
            ImGui::MenuItem("About Dear ImGui", NULL, nullptr);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}

void TitleBar::Update() {

    //Check if the application is fullscreen
    if (fullscreen) {
        // Monitor being used and current mode
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        // Get the screen width and height
        SCREEN_WIDTH = mode->width;
        SCREEN_HEIGHT = mode->height;

        // Set the window fullscreen
        glfwSetWindowSize(window, mode->width, mode->height);
    }
    else {
        // Set windowed
        SCREEN_WIDTH = WINDOWED_SCREEN_WIDTH;
        SCREEN_HEIGHT = WINDOWED_SCREEN_HEIGHT;

        glfwSetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    //Check if the exit button has been pressed
    if (exitPressed) {
        std::cout << "TITLE_BAR::UPDATE: User exited program" << std::endl;
        exit(1);
    }
}