#include "render_manager.h"

void RenderManager::StartUp()
{
    camera = Ref<Camera>(gUserInterface->GetCamera());

    renderableFactory = Ref<GLRenderableFactory>(new GLRenderableFactory);
    textureFactory = Ref<GLTextureFactory>(new GLTextureFactory);

    RenderCommands::CullBackFaces();
    RenderCommands::EnableDepthTest();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    finalTex = textureFactory->CreateEmptyTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA);

    glGenRenderbuffers(1, &finalRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, finalRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &finalFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, finalTex->GetHandle(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, finalRBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
        exit(1);
    }

    //Create the framebuffer which will replace the default frame buffer
    hdrTex = textureFactory->CreateEmptyTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA);

    glGenRenderbuffers(1, &hdrRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, hdrRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hdrTex->GetHandle(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, hdrRBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
        exit(1);
    }

    glGenFramebuffers(1, &mGeometricBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mGeometricBuffer);

    mGeometricPosition = textureFactory->CreateEmptyTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB16F);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mGeometricPosition->GetHandle(), 0);

    mGeometricNormal = textureFactory->CreateEmptyTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB16F);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mGeometricNormal->GetHandle(), 0);

    mGeometricAlbedoSpecular = textureFactory->CreateEmptyTexture(SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, mGeometricAlbedoSpecular->GetHandle(), 0);

    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };

    glDrawBuffers(3, attachments);

    glGenRenderbuffers(1, &mRBODepth);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBODepth); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mRBODepth);
    

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
    }
}

void RenderManager::Render() {
    double startTime = glfwGetTime();
    double totalTime = 0.0;

    int frames = 0;

    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    const unsigned int NR_LIGHTS = 5;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    srand(13);
    for (unsigned int i = 0; i < NR_LIGHTS; i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0f) * 15.0f;
        float yPos = ((rand() % 100) / 100.0f) * 15.0f;
        float zPos = ((rand() % 100) / 100.0f) * 15.0f;
        lightPositions.push_back(glm::vec3(xPos, yPos, zPos));
        // also calculate random color
        float rColor = ((rand() % 100) / 200.0f) + 0.1f; // between 0.5 and 1.0
        float gColor = ((rand() % 100) / 200.0f) + 0.1f; // between 0.5 and 1.0
        float bColor = ((rand() % 100) / 200.0f) + 0.1f; // between 0.5 and 1.0
        lightColors.push_back(glm::vec3(rColor, gColor, bColor));
    }

    Ref<Shader> lightShader(gShaderManager->GetShader(ShaderType::DEFERRED_LIGHTING));

    lightShader->Use();
    lightShader->SetInt("gPosition", 0);
    lightShader->SetInt("gNormal", 1);
    lightShader->SetInt("gAlbedoSpec", 2);
    lightShader->UnUse();

    Ref<Texture> boxTex = textureFactory->LoadRegularTexture("res/", "box.png", false);

    Ref<Renderable> box(new GLRectangle());
    Ref<Renderable> deferredBuffer(new GLRectangle());
    Ref<Renderable> hdrBuffer(new GLRectangle());
    Ref<Renderable> muro = renderableFactory->CreateModel("res/muro/muro.obj");
    Ref<Renderable> cube = renderableFactory->CreateCube();
    Ref<Renderable> ax(new GLAxisModel());

    std::string skyboxFiles[] = {
        "skybox2/right.png", 
        "skybox2/left.png", 
        "skybox2/top.png", 
        "skybox2/bottom.png", 
        "skybox2/front.png", 
        "skybox2/back.png"
    };

    Ref<Renderable> skybox(new GLSkyBox(skyboxFiles));

    gECM->AddDeferredEntity("Muro", muro);
    gECM->AddSkyboxEntity("Skybox", skybox);
    gECM->AddAxisEntity("Axis", ax);
    gECM->AddLightingPassEntity("Deferred Buffer", deferredBuffer);
    gECM->AddHdrBufferEntity("HDR Buffer", hdrBuffer, hdrTex);
    gECM->AddRegularEntity("Box", box, boxTex);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(gUserInterface->GetWindow()))
    {
        /* Poll for and process events */
        glfwPollEvents();

        double deltaTime = glfwGetTime() - startTime;
        startTime = glfwGetTime();
        totalTime += deltaTime;

        camera->Update(deltaTime);
        frames++;

        if (totalTime > 1.0) {
            frames = 0;
        }

        glm::mat4 viewMatrix(1.0f), projectionMatrix(1.0f);
        viewMatrix = camera->GetViewMatrix();
        projectionMatrix = camera->GetProjectionMatrix();


        /* Render here */
        RenderCommands::SetClearColour(gUserInterface->GetScreenClearColour());
        RenderCommands::Clear();

        Renderer::BeginScene(camera);

        //=======================================================================
        // Geometric Pass
        //=======================================================================
        glBindFramebuffer(GL_FRAMEBUFFER, mGeometricBuffer);
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Renderer::RenderDeferredGeometryBuffer();
        }
            
        //=======================================================================
        // Lighting pass
        //=======================================================================
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            lightShader->Use();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mGeometricPosition->GetHandle());
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, mGeometricNormal->GetHandle());
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, mGeometricAlbedoSpecular->GetHandle());

            for (unsigned int i = 0; i < lightPositions.size(); i++) {
                lightShader->SetVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
                lightShader->SetVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);

                const float linear = 0.005f;
                const float quadratic = 0.001f;

                lightShader->SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
                lightShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
            }

            Renderer::RenderDeferredLightingBuffer();
        }
            
        glBindFramebuffer(GL_READ_FRAMEBUFFER, mGeometricBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, hdrFBO); // write to default framebuffer

        // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
        // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
        // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
        glBlitFramebuffer(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

        //=======================================================================
        // Regular Blended Shading
        //=======================================================================
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        {
            //Start the regular shading for things that require blending or special lighting effects
            //Enable blending
            glEnable(GL_BLEND);

            Ref<Shader> basic = gShaderManager->GetShader(ShaderType::BASIC);

            basic->Use();
            basic->SetMat4("projection", projectionMatrix);
            basic->SetMat4("view", viewMatrix);
            for (size_t i = 0; i < lightPositions.size(); i++) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, lightPositions[i]);
                model = glm::scale(model, glm::vec3(0.125f));
                basic->SetMat4("model", model);
                basic->SetBool("textured", false);
                basic->SetVec3("colour", lightColors[i]);
                RenderCommands::DrawIndexed(cube, NULL, gShaderManager->GetShader(ShaderType::BASIC), camera);
            }
            basic->UnUse();

            Renderer::RenderRegularBuffer();

            //Disable blending as we are now done
            glDisable(GL_BLEND);
        }

        glBindTexture(GL_TEXTURE_2D, hdrTex->GetHandle());
        glGenerateTextureMipmap(hdrTex->GetHandle());
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Renderer::RenderHDRBuffer();
        
        glBindTexture(GL_TEXTURE_2D, finalTex->GetHandle());
        glGenerateTextureMipmap(finalTex->GetHandle());
        glBindTexture(GL_TEXTURE_2D, 0);

        Renderer::EndScene();

        gUserInterface->Update(finalTex->GetHandle(), hdrTex->GetHandle(), mGeometricAlbedoSpecular->GetHandle(), mGeometricNormal->GetHandle(), mGeometricPosition->GetHandle());
        gUserInterface->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(gUserInterface->GetWindow());
    }
}

void RenderManager::ShutDown()
{
}