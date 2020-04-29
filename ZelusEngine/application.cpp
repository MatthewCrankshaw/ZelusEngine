#include "application.h"


Application::Application() {
	Init();
    MainLoop();
}

Application::~Application(){

}

/**
 * @brief initialise windows, ui and other important compenents
 * 
 */
void Application::Init() {

    /* Initialize the library */
    if (!glfwInit()) {
        exit(1);
    }

    ui = new UserInterface();
    ui->Init();

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

    ui->SetCamera(cam);

    rm = new RenderManager(cam);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); //Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    ui->SetupGLFW(window); 
    ui->SetupOpenGL(glsl_version);


    
    glEnable(GL_MULTISAMPLE);

    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    

    glfwSetErrorCallback(InputHandler::OnWindowError);
    glfwSetKeyCallback(window, InputHandler::OnKey);
    glfwSetMouseButtonCallback(window, InputHandler::OnMouseButton);
    glfwSetCursorPosCallback(window, InputHandler::OnCursorPosition);
    glfwSetFramebufferSizeCallback(window, InputHandler::OnFrameBufferSizeChange);

    defaultShader = new Shader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl");
    lightShader = new Shader("Shaders/light_vertex.glsl", "Shaders/light_fragment.glsl");
    axisShader = new Shader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl");
    windowShader = new Shader("Shaders/window_vertex.glsl", "Shaders/window_fragment.glsl");
    skyboxShader = new Shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");

    //windowTexture = new Texture("res/", "blending_transparent_window.png", false); 
    //windowTexture->LoadRegularTexture("res/", "blending_transparent_window.png", false);
    //windowTexture = new Texture("res/", "flowers.png", true);
    //windowTexture->LoadRegularTexture("res/", "flowers.png", true);
    windowTexture = new Texture(); 
    windowTexture->LoadRegularTexture("res/", "transparent_grass.png", true);

    m = new Model("res/crysis_nano_suit/nanosuit.obj", ui);
    //m = new Model("res/skull/Skull.obj", ui);
    //m = new Model("res/SM_Fern_01.obj");
    //m = new Model("res/CarsN/LowPolyCars.obj", ui);
    //m = new Model("res/bugatti/bugatti.obj", ui);
    //m = new Model("res/buildings/Residential\ Buildings\ 003.obj", ui);
    //m = new Model("res/FireHydrant_Model/sm_FireHydrant.obj", ui);
    //m = new Model("res/Sample_Ship/Sample_Ship.obj", ui);
    //m = new Model("res/Valentine_balloon/W.obj", ui);

    std::vector<std::string> faces{
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg",
    };

    skyBox = new SkyBox(faces, ui);
    skyBox->setShader(skyboxShader);

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

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

void Application::MainLoop() {
    
    double startTime = glfwGetTime();
    double totalTime = 0.0f;

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

    defaultShader->Use();

    glm::vec3 pos;
    cam->GetPosition(pos);
    defaultShader->SetVec3("viewPos", pos);

    m->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));
    m->setShader(defaultShader);
    rm->Add(m);

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

        if (totalTime > 1.0f) {
            //totalTime = 0.0f;
            frames = 0.0;
        }

        glm::mat4 viewMatrix(1.0f), projectionMatrix(1.0f);
        cam->GetViewMatrix(viewMatrix);
        cam->GetProjectionMatrix(projectionMatrix);

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuff);


        /* Render here */
        ImVec4 clearColour = ui->GetScreenClearColour();
        glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 modelMatrix(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));

        //=========================================================================================

        rm->Render();

        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        defaultShader->UnUse();

        //=========================================================================================
        //=========================================================================================

        axisShader->Use();

        glm::mat4 axisModel = glm::mat4(1.0);
        glm::mat4 axisTranslate = glm::mat4(1.0);
        glm::mat4 axisScale = glm::mat4(1.0);
        glm::mat4 axisOrthProj = glm::mat4(1.0);

        glm::vec3 axisPos; 
        glm::vec3 axisForward;
        glm::fquat axisRot;

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

        //=========================================================================================
        /*
        glDisable(GL_DEPTH_TEST);
        glm::mat4 windowModel = glm::mat4(1.0f);
        glm::mat4 rotate = glm::mat4(1.0f);
        glm::mat4 translate = glm::mat4(1.0f);

        glm::fquat rotUpright = glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        rotate = glm::toMat4(rotUpright);
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        windowModel = rotate * translate;

        windowShader->Use();
        windowShader->SetInt("texture1", 0);
        windowShader->SetMat4("view", viewMatrix);
        windowShader->SetMat4("model", windowModel);
        windowShader->SetMat4("projection", projectionMatrix);

        glActiveTexture(windowTexture->GetHandle());
        glBindTexture(GL_TEXTURE_2D, windowTexture->GetHandle());
        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(0);

        for (int i = 0; i < 10; i++) {
            windowShader->SetInt("texture1", 0);
            windowShader->SetMat4("view", viewMatrix);
            windowShader->SetMat4("model", windowModel);
            windowShader->SetMat4("projection", projectionMatrix);

            glActiveTexture(windowTexture->GetHandle());
            glBindTexture(GL_TEXTURE_2D, windowTexture->GetHandle());
            glBindVertexArray(planeVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(0);

            windowModel = windowModel * translate;
        }
        glEnable(GL_DEPTH_TEST);

        windowShader->UnUse();*/

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, renderBuffTex);
        glGenerateTextureMipmap(renderBuffTex);
        glBindTexture(GL_TEXTURE_2D, 0);

        ui->Update(renderBuffTex);

        ui->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

    }
}

void Application::Cleanup() {

    free(defaultShader);
    free(lightShader);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    
}

void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}
void Application::CursorPositionCallback(GLFWwindow* window, double x, double y) {

}
void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    SCREEN_WIDTH = width; 
    SCREEN_HEIGHT = height;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}