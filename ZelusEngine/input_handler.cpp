#include "input_handler.h"

std::vector<InputHandler*> InputHandler::inputHandlerInstances;

InputHandler::InputHandler() {
	setInputHandler();
}

InputHandler::~InputHandler() = default;

/*!
 * If there is a glfw window error, onWindowError will be called
 * @param error - The integer error number
 * @param description - A description of what the error means
 */
void InputHandler::OnWindowError(int error, const char* description) {
    // Print Error message
    std::cerr << "Error: " << error << " : " << description << std::endl;
    exit(1);
}