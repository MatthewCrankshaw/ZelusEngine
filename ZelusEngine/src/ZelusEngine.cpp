// ZelusEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "user_interface.h"
#include "renderer/render_manager.h"
#include "log.h"
#include "entity_component_manager.h"
#include "shader_manager.h"

// Global Singletons 
// Should be started up in the order they are declared and then shut down in the reverse order
Ref<UserInterface> gUserInterface(new UserInterface());
Ref<Log> gLog(new Log());
Ref<ShaderManager> gShaderManager(new ShaderManager());
Ref<EntityComponentManager> gECM(new EntityComponentManager());
Ref<RenderManager> gRenderManager(new RenderManager());

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