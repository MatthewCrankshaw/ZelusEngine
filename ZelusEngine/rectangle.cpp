#include "rectangle.h"

Rectangle::Rectangle()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexData), mVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	mTextureId = 0;

	mColour = glm::vec3(0.3f, 0.3f, 0.3f);

	mShaderMode = ShaderModes::REGULAR;

	mTexturedRect = false;
}

Rectangle::Rectangle(glm::vec3 colour)
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexData), mVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	mTextureId = 0;

	mColour = colour;

	mShaderMode = ShaderModes::REGULAR;

	mTexturedRect = false;
}

Rectangle::Rectangle(std::string textureFilename)
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVertexData), mVertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	mTextureId = 0;

	mColour = glm::vec3(1.0f, 1.0f, 1.0f);

	mShaderMode = ShaderModes::REGULAR;

	Texture texture;
	texture.LoadRegularTexture("res/", textureFilename, true);
	mTextureId = texture.GetHandle();

	mTexturedRect = true;

}

void Rectangle::Draw(const Camera& camera)
{

	Shader* shader;
	switch (mShaderMode) {
	case ShaderModes::GEOMETRIC_PASS:
		shader = gShaderManager->getGeometryPassShader();
		break;
	case ShaderModes::LIGHTING_PASS:
		shader = gShaderManager->getLighthingPassShader();
		break;
	case ShaderModes::REGULAR:
		shader = gShaderManager->getBasicShader();
		break;
	default: 
		shader = gShaderManager->getBasicShader();
	}
	shader->Use();

	camera.GetViewMatrix(mViewMat);
	camera.GetProjectionMatrix(mProjectionMat);

	mModelMat = mTranslation * mRotation * mScale;

	shader->SetMat4("view", mViewMat);
	shader->SetMat4("projection", mProjectionMat);
	shader->SetMat4("model", mModelMat);

	glBindVertexArray(mVAO);
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

void Rectangle::Update()
{
}
