#include "render_manager.h"
#include "entity.h"


void RenderManager::StartUp()
{
    camera = Ref<Camera>(gUserInterface->GetCamera());

    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    glGenTextures(1, &finalTex);
    glBindTexture(GL_TEXTURE_2D, finalTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &finalRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, finalRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &finalFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, finalTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, finalRBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
        exit(1);
    }

    //Create the framebuffer which will replace the default frame buffer

    glGenTextures(1, &hdrBuffer);
    glBindTexture(GL_TEXTURE_2D, hdrBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &hdrRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, hdrRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCREEN_WIDTH, SCREEN_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, hdrBuffer, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, hdrRBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is not complete!" << std::endl;
        exit(1);
    }

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
        float xPos = ((rand() % 100) / 100.0) * 2.0 - 3.0;
        float yPos = ((rand() % 100) / 100.0) * 2.0 - 0.0;
        float zPos = ((rand() % 100) / 100.0) * 2.0 - 3.0;
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

    //model->setPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    Rectangle* quad = new Rectangle();
    Rectangle* quadHdr = new Rectangle();
    //Rectangle* rect = new Rectangle("flowers.png");

    Ref<Renderable> m(new Model("res/FireHydrant_Model/sm_FireHydrant.obj"));

    Ref<Renderable> m2(new Model("res/crysis_nano_suit/nanosuit.obj"));
    //Renderable* m = new Model("res/skull/Skull.obj");
    Ref<AxisModel> ax(new AxisModel());

    std::vector<std::string> skyboxFiles{
        "skybox/right.jpg", 
        "skybox/left.jpg", 
        "skybox/top.jpg", 
        "skybox/bottom.jpg", 
        "skybox/front.jpg", 
        "skybox/back.jpg"
    };

    Renderable* skybox = new SkyBox(skyboxFiles);

    Ref<Entity> entity(new Entity("Nano Suit", m2, camera));
    Ref<Entity> entity2(new Entity("Fire Hydrant", m, camera));
    Ref<Entity> entity3(new Entity("Fire Hydrant 2", m, camera));

    std::vector<Ref<Entity> > entities;
    entities.push_back(entity);
    entities.push_back(entity2); 
    entities.push_back(entity3); 

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
            //totalTime = 0.0f;
            frames = 0;
        }

        glm::mat4 viewMatrix(1.0f), projectionMatrix(1.0f);
        camera->GetViewMatrix(viewMatrix);
        camera->GetProjectionMatrix(projectionMatrix);


        /* Render here */
        RenderCommands::SetClearColour(gUserInterface->GetScreenClearColour());
        RenderCommands::Clear();

        //=======================================================================
        // Geometric Pass
        //=======================================================================
        glBindFramebuffer(GL_FRAMEBUFFER, mGeometricBuffer);
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            //Renderer::BeginScene(cam);

            
            //Renderer::Submit(m);

            //m2->SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));
            //Renderer::Submit(m2);
            

            //Renderer::EndScene();
            for(int i = 0; i < entities.size(); i++){
                entities[i]->Draw();
            }
        }
            
        //=======================================================================
        // Lighting pass
        //=======================================================================
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        {
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

                const float linear = 0.8;
                const float quadratic = 0.2;

                lightShader->SetFloat("lights[" + std::to_string(i) + "].Linear", linear);
                lightShader->SetFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
            }

            //RenderQuad();
            quad->SetShaderMode(Rectangle::ShaderModes::LIGHTING_PASS);
            quad->Draw(*camera);
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

            //Skybox should be the first thing to render now
            skybox->Draw(*camera);
            ax->Draw(*camera);

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

            //Disable blending as we are now done
            glDisable(GL_BLEND);
        }

        glBindTexture(GL_TEXTURE_2D, hdrBuffer);
        glGenerateTextureMipmap(hdrBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, finalFBO);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Shader* hdrShader = gShaderManager->getHDRShader();
            hdrShader->Use();
            hdrShader->SetInt("hdrBuffer", 0);
            hdrShader->SetFloat("exposure", gUserInterface->GetExposure());
            hdrShader->SetFloat("gamma", gUserInterface->GetGamma());
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, hdrBuffer); 
            quadHdr->SetShaderMode(Rectangle::ShaderModes::HDR_PASS);
            quadHdr->Draw(*camera);
            hdrShader->UnUse();

        
        glBindTexture(GL_TEXTURE_2D, finalTex);
        glGenerateTextureMipmap(finalTex);
        glBindTexture(GL_TEXTURE_2D, 0);

        gUserInterface->Update(finalTex, hdrBuffer, mGeometricAlbedoSpecular, mGeometricNormal, mGeometricPosition, entities);

        gUserInterface->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(gUserInterface->GetWindow());

    }
}

void RenderManager::ShutDown()
{
    
}

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