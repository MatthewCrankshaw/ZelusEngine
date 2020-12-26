#include "gl_rectangle.h"
#include "../../texture_factory/gl_texture_factory.h"
#include "../../gl_api/texture/gl_texture.h"

GLRectangle::GLRectangle()
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
	glGenBuffers(1, &mEbo);
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexData), mVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	mModelMat = glm::mat4(1.0f);

	mTextureId = 0;

	mColour = glm::vec3(0.3f, 0.3f, 0.3f);

	mShaderMode = ShaderModes::REGULAR;

	mTexturedRect = false;
}

GLRectangle::GLRectangle(glm::vec3 colour)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
	glGenBuffers(1, &mEbo);
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexData), mVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	mModelMat = glm::mat4(1.0f);

	mTextureId = 0;

	mColour = colour;

	mShaderMode = ShaderModes::REGULAR;

	mTexturedRect = false;
}

GLRectangle::GLRectangle(std::string textureFilename)
{
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);
	glGenBuffers(1, &mEbo);
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexData), mVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	mTextureId = 0;

	mModelMat = glm::mat4(1.0f);

	mColour = glm::vec3(1.0f, 1.0f, 1.0f);

	mShaderMode = ShaderModes::REGULAR;

	GLTextureFactory texFactory;
	Ref<Texture> texture = texFactory.LoadRegularTexture("res/", textureFilename, true);
	mTextureId = texture->GetHandle();

	mTexturedRect = true;

}

void GLRectangle::Draw(const Ref<Camera> camera)
{

	Ref<Shader> shader;
	switch (mShaderMode) {
	case ShaderModes::GEOMETRIC_PASS:
		shader = gShaderManager->getGeometryPassShader();
		break;
	case ShaderModes::LIGHTING_PASS:
		shader = gShaderManager->getLighthingPassShader();
		break;
	case ShaderModes::HDR_PASS:
		shader = gShaderManager->getHDRShader();
		break;
	case ShaderModes::REGULAR:
		shader = gShaderManager->getBasicShader();
		break;
	default: 
		shader = gShaderManager->getBasicShader();
	}
	shader->Use();

	shader->SetBool("textureProvided", true);

	glm::mat4 viewMat, projectionMat;
	camera->GetViewMatrix(viewMat);
	camera->GetProjectionMatrix(projectionMat);

	shader->SetMat4("view", viewMat);
	shader->SetMat4("projection", projectionMat);
	shader->SetMat4("model", mModelMat);

	glBindVertexArray(mVao);
	if (mTexturedRect) {
		shader->SetBool("textured", 1);
		shader->SetVec3("colour", mColour);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTextureId);
	}
	else {
	
		shader->SetBool("textured", 0);
		shader->SetVec3("colour", mColour);
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader->UnUse();
}

void GLRectangle::Update()
{
}
