// ZelusEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "render_manager.h"

UserInterfaceManager* gUserInterface = new UserInterfaceManager;
RenderManager* gRenderManager = new RenderManager;

int main()
{
    gUserInterface->StartUp();
    gRenderManager->StartUp();

    gRenderManager->Render();

    gRenderManager->ShutDown();
    gUserInterface->ShutDown();
}