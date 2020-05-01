// ZelusEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "render_manager.h"
#include "shader_manager.h"

// Global Singletons 
// Should be started up in the order they are declared and then shut down in the reverse order
UserInterfaceManager* gUserInterface = new UserInterfaceManager;
RenderManager* gRenderManager = new RenderManager;
ShaderManager* gShaderManager = new ShaderManager;

int main()
{
    gUserInterface->StartUp();
    gRenderManager->StartUp();
    gShaderManager->StartUp();

    gRenderManager->Render();

    gShaderManager->ShutDown();
    gRenderManager->ShutDown();
    gUserInterface->ShutDown();
}