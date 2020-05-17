// ZelusEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Renderer/render_manager.h"
#include "log.h"
#include "shader_manager.h"

// Global Singletons 
// Should be started up in the order they are declared and then shut down in the reverse order
UserInterface* gUserInterface = new UserInterface;
Log* gLog = new Log;
RenderManager* gRenderManager = new RenderManager;
ShaderManager* gShaderManager = new ShaderManager;

int main()
{
    gUserInterface  ->StartUp();
    gLog            ->StartUp();
    gRenderManager  ->StartUp();
    gShaderManager  ->StartUp();

    gRenderManager  ->Render();

    gShaderManager  ->ShutDown();
    gRenderManager  ->ShutDown();
    gLog            ->ShutDown();
    gUserInterface  ->ShutDown();
}