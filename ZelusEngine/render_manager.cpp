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

    //glfwWindowHint(GLFW_SAMPLES, 4);

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


    //glEnable(GL_MULTISAMPLE);

    glCullFace(GL_BACK);

    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetErrorCallback(InputHandler::OnWindowError);
    glfwSetKeyCallback(window, InputHandler::OnKey);
    glfwSetMouseButtonCallback(window, InputHandler::OnMouseButton);
    glfwSetCursorPosCallback(window, InputHandler::OnCursorPosition);
    glfwSetFramebufferSizeCallback(window, InputHandler::OnFrameBufferSizeChange);

    m = new Model("res/crysis_nano_suit/nanosuit.obj");
    //m = new Model("res/skull/Skull.obj", ui);
    //m = new Model("res/SM_Fern_01.obj");
    //m = new Model("res/CarsN/LowPolyCars.obj", ui);
    //m = new Model("res/bugatti/bugatti.obj", ui);
    //m = new Model("res/buildings/Residential\ Buildings\ 003.obj", ui);
    //m = new Model("res/FireHydrant_Model/sm_FireHydrant.obj");
    //m = new Model("res/Sample_Ship/Sample_Ship.obj", ui);
    //m = new Model("res/Valentine_balloon/W.obj", ui);

    axis = new AxisModel();

    std::vector<std::string> faces{
        "skybox/right.jpg",
        "skybox/left.jpg",
        "skybox/top.jpg",
        "skybox/bottom.jpg",
        "skybox/front.jpg",
        "skybox/back.jpg",
    };

    skyBox = new SkyBox(faces);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void RenderManager::Render() {
    double startTime = glfwGetTime();
    double totalTime = 0.0;

    int frames = 0;

    //Create the framebuffer which will replace the default frame buffer
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


    glGenFramebuffers(1, &mGeometricBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mGeometricBuffer);

    glGenTextures(1, &mGeometricPosition);
    glBindTexture(GL_TEXTURE_2D, mGeometricPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mGeometricPosition, 0);

    glGenTextures(1, &mGeometricNormal);
    glBindTexture(GL_TEXTURE_2D, mGeometricNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mGeometricNormal, 0);

    glGenTextures(1, &mGeometricAlbedoSpecular);
    glBindTexture(GL_TEXTURE_2D, mGeometricAlbedoSpecular);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mGeometricAlbedoSpecular, 0);

    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

    glDrawBuffers(3, attachments);

    glGenRenderbuffers(1, &mRBODepth);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBODepth); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRBODepth);
    

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuff);

    std::vector<glm::vec3> objectPositions;
    objectPositions.push_back(glm::vec3(-3.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, -3.0));
    objectPositions.push_back(glm::vec3(-3.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, 0.0));
    objectPositions.push_back(glm::vec3(-3.0, -3.0, 3.0));
    objectPositions.push_back(glm::vec3(0.0, -3.0, 3.0));
    objectPositions.push_back(glm::vec3(3.0, -3.0, 3.0));

    const unsigned int NR_LIGHTS = 5;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    srand(13);
    for (unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = ((rand() % 100) / 100.0) * 6.0 - 4.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
        // also calculate random color
        float rColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float gColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        float bColor = ((rand() % 100) / 200.0f) + 0.5; // between 0.5 and 1.0
        lightColors.push_back(glm::vec3(rColor, gColor, bColor));
    }

    Shader* lightShader = gShaderManager->getLighthingPassShader();

    lightShader->Use();
    lightShader->SetInt("gPosition", 0);
    lightShader->SetInt("gNormal", 1);
    lightShader->SetInt("gAlbedoSpec", 2);

    lightShader->UnUse();

    m->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    Rectangle* quad = new Rectangle();
    Rectangle* rect = new Rectangle("flowers.png");

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


        /* Render here */
        ImVec4 clearColour = gUserInterface->GetScreenClearColour();
        glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Geometric Pass
        glBindFramebuffer(GL_FRAMEBUFFER, mGeometricBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (int i = 0; i < objectPositions.size(); i++) {
            m->setPosition(objectPositions[i]);
            m->setScale(glm::vec3(0.25f));
            m->Draw(*cam);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuff);

        //Lighting pass
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightShader->Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mGeometricPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mGeometricNormal);
        glActiveTexture(GL_TEXTURE2); 
        glBindTexture(GL_TEXTURE_2D, mGeometricAlbedoSpecular);

        for (unsigned int i = 0; i < lightPositions.size(); i++) {
            lightShader->SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
            lightShader->SetVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);

            const float linear = 0.2; 
            const float quadratic = 0.03; 

            lightShader->SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
            lightShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
        }

        //glm::vec3 camPos;
        //cam->GetPosition(camPos);
        //lightShader->SetVec3("viewPos", camPos);

        //RenderQuad();
        quad->SetShaderMode(Rectangle::ShaderModes::LIGHTING_PASS);
        quad->Draw(*cam);

        glBindFramebuffer(GL_READ_FRAMEBUFFER, mGeometricBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuff); // write to default framebuffer

        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuff);

        //Start the regular shading for things that require blending or special lighting effects
        //Enable blending
        glEnable(GL_BLEND);

        //Skybox should be the first thing to render now
        skyBox->Draw(*cam);

        Shader* basic = gShaderManager->getBasicShader();

        basic->Use();
        basic->SetMat4("projection", projectionMatrix);
        basic->SetMat4("view", viewMatrix);
        for (int i = 0; i < lightPositions.size(); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, lightPositions[i]);
            model = glm::scale(model, glm::vec3(0.125f));
            basic->SetMat4("model", model);
            basic->SetBool("textured", false);
            basic->SetVec3("colour", lightColors[i]);
            RenderCube();
        }
        basic->UnUse();

        rect->setPosition(glm::vec3(0.0f, 1.5f, 0.0f));
        rect->Draw(*cam);
        
        //Disable blending as we are now done
        glDisable(GL_BLEND);

        //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, renderBuffTex, 0);
        glBindTexture(GL_TEXTURE_2D, renderBuffTex);
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

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
//unsigned int quadVAO = 0;
//unsigned int quadVBO;
//void RenderManager::RenderQuad()
//{
//    if (quadVAO == 0)
//    {
//        float quadVertices[] = {
//            // positions        // texture Coords
//            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
//            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//             1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
//             1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//        };
//        // setup plane VAO
//        glGenVertexArrays(1, &quadVAO);
//        glGenBuffers(1, &quadVBO);
//        glBindVertexArray(quadVAO);
//        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    }
//    glBindVertexArray(quadVAO);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//    glBindVertexArray(0);
//}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void RenderManager::RenderCube()
{
    // initialize (if necessary)
    if (cubeVAO == 0)
    {
        float vertices[] = {
            // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
        };
        glGenVertexArrays(1, &cubeVAO);
        glGenBuffers(1, &cubeVBO);
        // fill buffer
        glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // link vertex attributes
        glBindVertexArray(cubeVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}