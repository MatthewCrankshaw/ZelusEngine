
#include "user_interface.h"



void UserInterface::StartUp() {

    fov = 45.0f;
    exitPressed - false;
    gameWindowNoMove = true;
    gammaCorrection = false;
    logEnabled = true;
    mGeometricAlbedoOutput = true;
    mGeometricNormalOutput = true;
    mGeometricPositionOutput = true;
    mHDROutput = true;

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

    /* Initialize the library */
    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Enable vsync

    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    camera = Ref<Camera>(new Camera());

    SetupGLFW();
    SetupOpenGL();
}

void UserInterface::ShutDown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void UserInterface::SetupGLFW()
{
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    
    ui_handler = new UserInterfaceInputHandler(window, camera);

    glfwSetErrorCallback(InputHandler::OnWindowError);
    glfwSetKeyCallback(window, InputHandler::OnKey);
    glfwSetMouseButtonCallback(window, InputHandler::OnMouseButton);
    glfwSetCursorPosCallback(window, InputHandler::OnCursorPosition);
    glfwSetFramebufferSizeCallback(window, InputHandler::OnFrameBufferSizeChange);

}

void UserInterface::SetupOpenGL()
{
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void UserInterface::Update(GLuint imageOutput, GLuint hdrOutput, GLuint gAlbedoOutput, GLuint gNormalOutput, GLuint gPositionOutput)
{
    if (camera == nullptr) {
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

void UserInterface::UpdateTitleWindow() {
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
    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);           // Use fixed width for labels (by passing a negative value), the rest goes to widgets. We choose a width proportional to our font size.

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
            ImGui::MenuItem("Log", NULL, &logEnabled);
            ImGui::MenuItem("Albedo View", NULL, &mGeometricAlbedoOutput);
            ImGui::MenuItem("Normal View", NULL, &mGeometricNormalOutput);
            ImGui::MenuItem("Position View", NULL, &mGeometricPositionOutput);
            ImGui::MenuItem("HDR View", NULL, &mHDROutput);
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

    //Check if the exit button has been pressed
    if (exitPressed) {
        std::cout << "TITLE_BAR::UPDATE: User exited program" << std::endl;
        exit(1);
    }
}

void UserInterface::UpdateGameWindow(GLuint imageOutput) {
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoCollapse;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    if (gameWindowNoMove) windowFlagsGame |= ImGuiWindowFlags_NoMove;

    ImGui::Begin("Game Window", NULL, windowFlagsGame);
    ui_handler->EngineInputHandler();
    ImVec2 size = ImGui::GetWindowSize();
    //SCREEN_WIDTH = (int)size.x - 100;
    //SCREEN_HEIGHT = (int)size.y - 100;

    camera->FramebufferSizeCallback(window, (int)size.x - 100, (int)size.y - 100);
    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterface::UpdateHDRWindow(GLuint imageOutput)
{
    if (!mHDROutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("HDR Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterface::UpdatePositionWindow(GLuint imageOutput)
{
    if (!mGeometricPositionOutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Position Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterface::UpdateAlbedoWindow(GLuint imageOutput)
{
    if (!mGeometricAlbedoOutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Albedo Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterface::UpdateNormalWindow(GLuint imageOutput)
{
    if (!mGeometricNormalOutput) return;
    ImGuiWindowFlags windowFlagsGame = 0;
    windowFlagsGame |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Normal Window", NULL, windowFlagsGame);
    ImVec2 size = ImGui::GetWindowSize();

    ImGui::Image((void*)imageOutput, ImVec2(size.x, size.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

void UserInterface::UpdatePropertiesWindow() {
    ImGuiWindowFlags windowFlagsProperties = 0;
    windowFlagsProperties |= ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Properties", NULL, windowFlagsProperties);                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::SliderFloat("Field Of View", &fov, 5.0f, 180.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    camera->SetFieldOfView(fov);

    ImGui::ColorEdit3("clear color", (float*)&clearColour); // Edit 3 floats representing a color

    ImGui::SliderFloat("Exposure", &exposure, 0.01f, 5.0f);
    ImGui::SliderFloat("Gamma", &gamma, 0.5f, 4.0f);

    if (ImGui::Button("Game Window No Move")) {
        gameWindowNoMove = !gameWindowNoMove;
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::End();
    
}

void UserInterface::UpdateLogWindow() {
    ImGuiWindowFlags windowFlagsLog = 0;
    bool demo = true;

    if (!logEnabled) return;
    ImGui::ShowDemoWindow(&demo);
    gLog->Draw("Log", &demo);
}


void UserInterface::Render() {
    
    if (camera == nullptr) {
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

void UserInterface::ToggleBool(bool& value) {
    value = !value;
}