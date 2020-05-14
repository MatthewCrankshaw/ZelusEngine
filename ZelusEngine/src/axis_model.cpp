#include "axis_model.h"

AxisModel::AxisModel()
{
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void AxisModel::Draw(const Camera& camera)
{
    Shader* shader = gShaderManager->getAxisShader();
    shader->Use();

    glm::vec3 pos;
    glm::vec3 forward;

    camera.GetPosition(pos);
    camera.GetForward(forward);
    camera.GetProjectionMatrix(mProjectionMat);
    camera.GetViewMatrix(mViewMat);

    mTranslation = glm::translate(glm::mat4(1.0), pos + (forward * glm::vec3(2.0)));
    mScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f));

    mModelMat = mTranslation * mScale;

    shader->SetMat4("view", mViewMat);
    shader->SetMat4("model", mModelMat);
    shader->SetMat4("projection", mProjectionMat);

    glDisable(GL_DEPTH_TEST);
    glLineWidth(5.0f);
    glPointSize(10.0f);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_LINES, 0, 14);
    glDrawArrays(GL_POINTS, 0, 14);
    glBindVertexArray(0);
    glPointSize(1.0f);
    glLineWidth(1.0f);
    glEnable(GL_DEPTH_TEST);

    shader->UnUse();
}

void AxisModel::Update()
{
}
