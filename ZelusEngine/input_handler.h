#pragma once

#include <iostream>
#include <vector>
#include <map>

#include <GLFW/glfw3.h>

class InputHandler
{
public: 
	InputHandler(); 

	~InputHandler();

	virtual void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
	virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) = 0;
	virtual void CursorPositionCallback(GLFWwindow* window, double x, double y) = 0;
	virtual void FramebufferSizeCallback(GLFWwindow* window, int width, int height) = 0;

	static std::vector<InputHandler*> inputHandlerInstances;
	virtual void setInputHandler(){ inputHandlerInstances.emplace_back(this); }

    static void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (!inputHandlerInstances.empty()) {
            for (auto callback : inputHandlerInstances) {
                callback->KeyCallback(window, key, scancode, action, mods);
            }
        }
    }

    static void OnMouseButton(GLFWwindow* window, int button, int action, int mods) {
        if (!inputHandlerInstances.empty()) {
            for (auto callback : inputHandlerInstances) {
                callback->MouseButtonCallback(window, button, action, mods);
            }
        }
    }

    static void OnCursorPosition(GLFWwindow* window, double x, double y) {
        if (!inputHandlerInstances.empty()) {
            for (auto callback : inputHandlerInstances) {
                callback->CursorPositionCallback(window, x, y);
            }
        }
    }

    static void OnFrameBufferSizeChange(GLFWwindow* window, int width, int height) {
        if (!inputHandlerInstances.empty()) {
            for (auto callback : inputHandlerInstances) {
                callback->FramebufferSizeCallback(window, width, height);
            }

        }
    }

    static void OnWindowError(int error, const char* description);

};

