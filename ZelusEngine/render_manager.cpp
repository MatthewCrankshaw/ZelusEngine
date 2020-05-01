#include "render_manager.h"


void RenderManager::StartUp()
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(1);
    }

    cam = new Camera();

    gUserInterface->SetCamera(cam);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    gUserInterface->SetupGLFW(window);
    gUserInterface->SetupOpenGL(glsl_version);


    glEnable(GL_MULTISAMPLE);

    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetErrorCallback(InputHandler::OnWindowError);
    glfwSetKeyCallback(window, InputHandler::OnKey);
    glfwSetMouseButtonCallback(window, InputHandler::OnMouseButton);
    glfwSetCursorPosCallback(window, InputHandler::OnCursorPosition);
    glfwSetFramebufferSizeCallback(window, InputHandler::OnFrameBufferSizeChange);

    multiLightShader = new Shader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl");
    axisShader = new Shader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl");
    skyBoxShader = new Shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
    basicShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");

    m = new Model("res/crysis_nano_suit/nanosuit.obj");
    //m = new Model("res/skull/Skull.obj", ui);
    //m = new Model("res/SM_Fern_01.obj");
    //m = new Model("res/CarsN/LowPolyCars.obj", ui);
    //m = new Model("res/bugatti/bugatti.obj", ui);
    //m = new Model("res/buildings/Residential\ Buildings\ 003.obj", ui);
    //m = new Model("res/FireHydrant_Model/sm_FireHydrant.obj", ui);
    //m = new Model("res/Sample_Ship/Sample_Ship.obj", ui);
    //m = new Model("res/Valentine_balloon/W.obj", ui);

    rect = new Rectangle("flowers.png");

    std::vector<std::string> faces{
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg",
    };

    skyBox = new SkyBox(faces);

    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);
    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), &axisVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void RenderManager::Render() {
    double startTime = glfwGetTime();
    double totalTime = 0.0;

    int frames = 0;

    GLuint frameBuff, renderBuffTex, rboId;

    glGenTextures(1, &renderBuffTex);
    glBindTexture(GL_TEXTURE_2D, renderBuffTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &frameBuff);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuff);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderBuffTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboId);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        double deltaTime = glfwGetTime() - startTime;
        startTime = glfwGetTime();
        totalTime += deltaTime;

        cam->Update(deltaTime);
        frames++;

        if (totalTime > 1.0) {
            //totalTime = 0.0f;
            frames = 0;
        }

        glm::mat4 viewMatrix(1.0f), projectionMatrix(1.0f);
        cam->GetViewMatrix(viewMatrix);
        cam->GetProjectionMatrix(projectionMatrix);

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuff);


        /* Render here */
        ImVec4 clearColour = gUserInterface->GetScreenClearColour();
        glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));

        //=========================================================================================
        //=========================================================================================

        axisShader->Use();

        glm::mat4 axisModel = glm::mat4(1.0);
        glm::mat4 axisTranslate = glm::mat4(1.0);
        glm::mat4 axisScale = glm::mat4(1.0);
        glm::mat4 axisOrthProj = glm::mat4(1.0);

        glm::vec3 axisPos;
        glm::vec3 axisForward;

        cam->GetPosition(axisPos);
        cam->GetForward(axisForward);
        cam->GetOrthoProjectionMatrix(axisOrthProj);

        axisTranslate = glm::translate(glm::mat4(1.0), axisPos + axisForward);
        axisScale = glm::scale(axisScale, glm::vec3(0.2f, 0.2f, 0.2f));

        axisModel = axisTranslate * axisScale;

        axisShader->SetMat4("view", viewMatrix);
        axisShader->SetMat4("model", axisModel);
        axisShader->SetMat4("projection", axisOrthProj);

        glLineWidth(5.0f);
        glPointSize(10.0f);
        glBindVertexArray(axisVAO);
        glDrawArrays(GL_LINES, 0, 14);
        glDrawArrays(GL_POINTS, 0, 14);
        glBindVertexArray(0);
        glPointSize(1.0f);
        glLineWidth(1.0f);

        axisShader->UnUse();

        //=========================================================================================

        skyBox->Draw(*cam);

        m->Draw(*cam);

        rect->Draw(*cam);

        //==========================================================================================

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, renderBuffTex);
        glGenerateTextureMipmap(renderBuffTex);
        glBindTexture(GL_TEXTURE_2D, 0);

        gUserInterface->Update(renderBuffTex);

        gUserInterface->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

    }
}

void RenderManager::ShutDown()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void RenderManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void RenderManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}
void RenderManager::CursorPositionCallback(GLFWwindow* window, double x, double y) {

}
void RenderManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}