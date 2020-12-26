// ZelusEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "renderer/render_manager.h"
#include "log.h"
#include "entity_component_manager.h"
#include "shader_manager.h"

// Global Singletons 
// Should be started up in the order they are declared and then shut down in the reverse order
UserInterface* gUserInterface = new UserInterface;
Log* gLog = new Log;
ShaderManager* gShaderManager = new ShaderManager;
EntityComponentManager* gECM = new EntityComponentManager;
RenderManager* gRenderManager = new RenderManager;

int main()
{
    gUserInterface  ->StartUp();
    gLog            ->StartUp();
    gShaderManager  ->StartUp();
    gECM            ->StartUp();
    gRenderManager  ->StartUp();

    gRenderManager  ->Render();

    gRenderManager  ->ShutDown();
    gECM            ->ShutDown();
    gShaderManager  ->ShutDown();
    gLog            ->ShutDown();
    gUserInterface  ->ShutDown();
}