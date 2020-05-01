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

	mShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");

	mTextureId = 0;

	mColour = glm::vec3(0.3f, 0.3f, 0.3f);

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

	mShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");

	mTextureId = 0;

	mColour = colour;

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

	mShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");

	mTextureId = 0;

	mColour = glm::vec3(1.0f, 1.0f, 1.0f);

	Texture texture;
	texture.LoadRegularTexture("res/", textureFilename, true);
	mTextureId = texture.GetHandle();

	mTexturedRect = true;

}

void Rectangle::Draw(const Camera& camera)
{
	mShader->Use();

	camera.GetViewMatrix(mViewMat);
	camera.GetProjectionMatrix(mProjectionMat);

	mModelMat = mTranslation * mRotation * mScale;

	mShader->SetMat4("view", mViewMat);
	mShader->SetMat4("projection", mProjectionMat);
	mShader->SetMat4("model", mModelMat);

	glBindVertexArray(mVAO);
	if (mTexturedRect) {
		mShader->SetBool("textured", 1);
		mShader->SetVec3("colour", mColour);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mTextureId);
	}
	else {
	
		mShader->SetBool("textured", 0);
		mShader->SetVec3("colour", mColour);
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	mShader->UnUse();
}

void Rectangle::Update()
{
}
