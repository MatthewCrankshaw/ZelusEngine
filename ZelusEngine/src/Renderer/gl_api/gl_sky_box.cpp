#include "gl_sky_box.h"

/**
 * \brief Creates a renderable cubemap
 * 
 * \param textureFacesFilenames A vector of all of the cubemap texture files in the order right, left, top, bottom, front, back
 */
GLSkyBox::GLSkyBox(std::vector<std::string> textureFacesFilenames)
{
	// Create vertex array object and vertex buffer object
	glGenVertexArrays(1, &mVao);
	glGenBuffers(1, &mVbo);

	// Bind the vertex array object and buffer
	glBindVertexArray(mVao);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);

	// Buffer the cube data 
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	// We only create vertex array for the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Create a texture object and load the cubemap
	Texture texture;
	texture.LoadCubeMapTexture("res/", textureFacesFilenames, false);

	// The texture handle is for a cubemap
	textureID = texture.GetHandle();

	mModelMat = glm::mat4(1.0f);
	mTranslation = glm::mat4(1.0f);
	mRotation = glm::mat4(1.0f);
	mScale = glm::mat4(1.0f);
}

void GLSkyBox::Draw(const Ref<Camera> camera)
{
	Shader* shader = gShaderManager->getSkyBoxShader(); 

	glDepthFunc(GL_LEQUAL); 
	shader->Use();

	glm::vec3 position;
	glm::mat4 viewMat, projectionMat;

	camera->GetViewMatrix(viewMat);
	camera->GetProjectionMatrix(projectionMat);
	camera->GetPosition(position);

	SetPosition(position);
	mModelMat = mTranslation * mRotation * mScale;
	shader->SetMat4("view", viewMat);
	shader->SetMat4("projection", projectionMat);
	shader->SetMat4("model", mModelMat);

	glBindVertexArray(mVao); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	shader->UnUse();
	glDepthFunc(GL_LESS);
}

void GLSkyBox::Update()
{
}

void GLSkyBox::SetPosition(const glm::vec3 position) {
	mPosition = position;
	mTranslation = glm::translate(glm::mat4(1.0f), mPosition);
}

GLuint GLSkyBox::getTextureId() {
	return textureID;
}
