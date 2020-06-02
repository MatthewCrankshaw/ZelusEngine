#include "ui_input_handler.h"

UserInterfaceInputHandler::UserInterfaceInputHandler(GLFWwindow* window, Ref<Camera> cam) {
	this->window = window; 
	this->cam = cam;
}

UserInterfaceInputHandler::~UserInterfaceInputHandler() {

}

void UserInterfaceInputHandler::EngineInputHandler() {

    ImGuiIO *io = &ImGui::GetIO(); (void)io;

    mouseDown = io->MouseDown[0];
    mouseRelease = io->MouseReleased[0];

    keyPress[GLFW_KEY_ESCAPE] = io->KeysDown[GLFW_KEY_ESCAPE];
    keyPress[GLFW_KEY_W] = io->KeysDown[GLFW_KEY_W];
    keyPress[GLFW_KEY_A] = io->KeysDown[GLFW_KEY_A];
    keyPress[GLFW_KEY_S] = io->KeysDown[GLFW_KEY_S];
    keyPress[GLFW_KEY_D] = io->KeysDown[GLFW_KEY_D];


    if (ImGui::IsWindowFocused()) {
        if (mouseDown) {
            cam->MouseButtonCallback(window, GLFW_MOUSE_BUTTON_1, GLFW_PRESS, 0);
            cam->CursorPositionCallback(window, io->MouseDelta.x, io->MouseDelta.y);
        }

        if (mouseRelease) {
            cam->MouseButtonCallback(window, GLFW_MOUSE_BUTTON_1, GLFW_RELEASE, 0);
            cam->CursorPositionCallback(window, io->MousePos.x, io->MousePos.y);
        }

        if (keyPress[GLFW_KEY_W]) {
            cam->KeyCallback(window, GLFW_KEY_W, 0, GLFW_PRESS, 0);
        }
        else {
            cam->KeyCallback(window, GLFW_KEY_W, 0, GLFW_RELEASE, 0);
        }

        if (keyPress[GLFW_KEY_A]) {
            cam->KeyCallback(window, GLFW_KEY_A, 0, GLFW_PRESS, 0);
        }
        else {
            cam->KeyCallback(window, GLFW_KEY_A, 0, GLFW_RELEASE, 0);
        }

        if (keyPress[GLFW_KEY_S]) {
            cam->KeyCallback(window, GLFW_KEY_S, 0, GLFW_PRESS, 0);
        }
        else {
            cam->KeyCallback(window, GLFW_KEY_S, 0, GLFW_RELEASE, 0);
        }

        if (keyPress[GLFW_KEY_D]) {
            cam->KeyCallback(window, GLFW_KEY_D, 0, GLFW_PRESS, 0);
        }
        else {
            cam->KeyCallback(window, GLFW_KEY_D, 0, GLFW_RELEASE, 0);
        }
    }
}