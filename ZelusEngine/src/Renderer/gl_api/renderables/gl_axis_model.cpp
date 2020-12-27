#include "gl_axis_model.h"

GLAxisModel::GLAxisModel()
{
    glGenVertexArrays(1, &mVao);
    glGenBuffers(1, &mVbo);
    glBindVertexArray(mVao);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), &mVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
}

void GLAxisModel::Draw(const Ref<Camera> camera)
{
    glLineWidth(5.0f);
    glPointSize(10.0f);
    glBindVertexArray(mVao);
    glDrawArrays(GL_LINES, 0, 14);
    glDrawArrays(GL_POINTS, 0, 14);
    glBindVertexArray(0);
    glPointSize(1.0f);
    glLineWidth(1.0f);
}

void GLAxisModel::Update()
{
}
