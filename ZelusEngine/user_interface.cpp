
#include "user_interface.h"

void UserInterfaceManager::StartUp() {

    fov = 45.0f;
    lightPosition[0] = 0.5f;
    lightPosition[1] = 0.5f;
    lightPosition[2] = 0.0f;
    lightDirection[0] = 0.0f;
    lightDirection[1] = 0.0f;
    lightDirection[2] = -1.0f;
    depthBufferEnabled = true;
    polyModeEnabled = false;
    cullFaceEnabled = true;
    gameWindowNoMove = true;
    gammaCorrection = false;
    mGeometricAlbedoOutput = true;
    mGeometricNormalOutput = true;
    mGeometricPositionOutput = true;
    mHDROutput = true;
    titleBarUI = new TitleBar();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io->ConfigViewportsNoAutoMerge = true;
    io->ConfigViewportsNoTaskBarIcon = true;

    //ImGui::StyleColorsClassic();
    //ImGui::StyleColorsLight();
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}

void UserInterfaceManager::ShutDown()
{

}

void UserInterfaceManager::SetupGLFW(GLFWwindow* window)
{
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    
    ui_handler = new UserInterfaceInputHandler(window, cam);

    titleBarUI->SetupGLFW(window);

    depthBufferEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    polyModeEnabled ? glPolygonMode(GL_FRONT, GL_LINE) : glPolygonMode(GL_FRONT, GL_FILL);

}

void UserInterfaceManager::SetupOpenGL(const char* glslVersion)
{
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void UserInterfaceManager::SetCamera(Camera* cam)
{
    this->cam = cam;
}

void UserInterfaceManager::Update(GLuint imageOutput, GLuint hdrOutput, GLuint gAlbedoOutput, GLuint gNormalOutput, GLuint gPositionOutput)
{
    if (cam == nullptr) {
        std::cout << "USER_INTERFACE::UPDATE: Camera object is null! Camera must be set up before updating or rendering!" << std::endl;
        exit(1);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    UpdateTitleWindow();

    UpdateGameWindow(imageOutput);
    UpdateHDRWindow(hdrOutput);
    UpdateAlbedoWindow(gAlbedoOutput);
    UpdateNormalWindow(gNormalOutput);
    UpdatePositionWindow(gPositionOutput);

    UpdatePropertiesWindow();

    UpdateLogWindow();
}

void UserInterfaceManager::UpdateTitleWindow() {
    titleBarUI->CreateTitleBar();
    titleBarUI->Update();
}

void UserInterfaceManager::UpdateGameWindow(GLuint imageOutput) {
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoCollapse;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (gameWindowNoMove) windowFlagsGame |= ImGuiWindowFlags_NoMove;

    ImGui::Begin("Game Window", NULL, windowFlagsGame);
    ui_handler->EngineInputHandler();
    ImVec2 size = ImGui::GetWindowSize();
    //SCREEN_WIDTH = (int)size.x - 100;
    //SCREEN_HEIGHT = (int)size.y - 100;

    cam->FramebufferSizeCallback(window, (int)size.x - 100, (int)size.y - 100);
    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterfaceManager::UpdateHDRWindow(GLuint imageOutput)
{
    if (!mHDROutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("HDR Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterfaceManager::UpdatePositionWindow(GLuint imageOutput)
{
    if (!mGeometricPositionOutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Position Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterfaceManager::UpdateAlbedoWindow(GLuint imageOutput)
{
    if (!mGeometricAlbedoOutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Albedo Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterfaceManager::UpdateNormalWindow(GLuint imageOutput)
{
    if (!mGeometricNormalOutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Normal Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterfaceManager::UpdatePropertiesWindow() {
    ImGuiWindowFlags windowFlagsProperties = 0;
    windowFlagsProperties |= ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Properties", NULL, windowFlagsProperties);                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::SliderFloat("Field Of View", &fov, 10.0f, 60.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    cam->SetFieldOfView(fov);

    if (ImGui::Button("Toggle Albedo Output")) {
        ToggleBool(mGeometricAlbedoOutput);
    }
    if (ImGui::Button("Toggle HDR Output")) {
        ToggleBool(mHDROutput);
    }
    ImGui::SameLine();
    if (ImGui::Button("Toggle Normal Output")) {
        ToggleBool(mGeometricNormalOutput);
    }
    ImGui::SameLine();
    if (ImGui::Button("Toggle Position Output")) {
        ToggleBool(mGeometricPositionOutput);
    }

    ImGui::ColorEdit3("clear color", (float*)&clearColour); // Edit 3 floats representing a color

    ImGui::Text("Light");
    /*ImGui::SliderFloat3("Light Position", lightPosition, -20.0f, 20.0f);
    ImGui::SliderFloat3("Light Direction", lightDirection, -1.0f, 1.0f);
    ImGui::ColorEdit3("Ambient", (float*)&lightAmbient);
    ImGui::ColorEdit3("Diffuse", (float*)&lightDiffuse);
    ImGui::ColorEdit3("Specular", (float*)&lightSpecular);
    ImGui::SliderFloat("Constant", &lightConstant, 0.1f, 1.0f);
    ImGui::SliderFloat("Linear", &lightLinear, 0.0001f, 2.0f);
    ImGui::SliderFloat("Quadratic", &lightQuadratic, 0.000007f, 2.0f);
    ImGui::SliderFloat("Inner CutOff", &lightInnerCutOff, 10.0f,40.0f);
    ImGui::SliderFloat("Outer CutOff", &lightOuterCutOff, 10.0f, 40.0f);*/
    ImGui::SliderFloat("Exposure", &exposure, 0.01f, 5.0f);
    ImGui::SliderFloat("Gamma", &gamma, 0.5f, 4.0f);

    /*ImGui::Text("Material Colors");
    ImGui::ColorEdit3("material ambient", (float*)&materialAmbient);
    ImGui::ColorEdit3("material diffuse", (float*)&materialDiffuse);
    ImGui::ColorEdit3("material specular", (float*)&materialSpecular);
    ImGui::SliderFloat("Shininess: ", &materialShininess, 0.0f, 50.0f);*/

    if (ImGui::Button("Toggle Depth Test")) {
        ToggleDeptTest();
        depthBufferEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }
    ImGui::SameLine();
    if (ImGui::Button("Toggle Polygon Mode")) {
        polyModeEnabled ? glPolygonMode(GL_FRONT, GL_LINE) : glPolygonMode(GL_FRONT, GL_FILL);
        ToggleBool(polyModeEnabled);
    }
    ImGui::SameLine();
    if (ImGui::Button("Toggle Cull Face")) {
        cullFaceEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
        ToggleCullFace();
    }
    if (ImGui::Button("Game Window No Move")) {
        gameWindowNoMove = !gameWindowNoMove;
    }
    ImGui::SameLine();
    if (ImGui::Button("Gamma Correction")) {
        gammaCorrection ? glEnable(GL_FRAMEBUFFER_SRGB) : glDisable(GL_FRAMEBUFFER_SRGB);
        ToggleGammaCorrection();
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void UserInterfaceManager::UpdateLogWindow() {
    ImGuiWindowFlags windowFlagsLog = 0;
    bool demo = true;
    ImGui::ShowDemoWindow(&demo);
    ImGui::Begin("Log", NULL, windowFlagsLog);
    ImGui::End();
}


void UserInterfaceManager::Render() {
    
    if (cam == nullptr) {
        std::cout << "USER_INTERFACE::RENDERER: Camera object is null! Camera must be set up before updating or rendering!" << std::endl;
        exit(1);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void UserInterfaceManager::ToggleBool(bool& value) {
    value = !value;
}

void UserInterfaceManager::ToggleDeptTest() {
    depthBufferEnabled = !depthBufferEnabled;
}

void UserInterfaceManager::TogglePolyMode() {
    polyModeEnabled = !polyModeEnabled; 
}

void UserInterfaceManager::ToggleCullFace() {
    cullFaceEnabled = !cullFaceEnabled;
}

void UserInterfaceManager::ToggleGammaCorrection()
{
    gammaCorrection = !gammaCorrection;
}
