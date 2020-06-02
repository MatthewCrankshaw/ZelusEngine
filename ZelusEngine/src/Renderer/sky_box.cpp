#include "sky_box.h"

/**
 * \brief Creates a renderable cubemap
 * 
 * \param textureFacesFilenames A vector of all of the cubemap texture files in the order right, left, top, bottom, front, back
 */
SkyBox::SkyBox(std::vector<std::string> textureFacesFilenames)
{
	// Create vertex array object and vertex buffer object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the vertex array object and buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

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
}

void SkyBox::Draw(const Camera& camera)
{
	Shader* shader = gShaderManager->getSkyBoxShader(); 

	glDepthFunc(GL_LEQUAL); 
	shader->Use();

	glm::vec3 position;

	camera.GetViewMatrix(mViewMat);
	camera.GetProjectionMatrix(mProjectionMat);
	camera.GetPosition(position);

	SetPosition(position);
	mModelMat = mTranslation * mRotation * mScale;
	shader->SetMat4("view", mViewMat);
	shader->SetMat4("projection", mProjectionMat);
	shader->SetMat4("model", mModelMat);

	glBindVertexArray(VAO); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	shader->UnUse();
	glDepthFunc(GL_LESS);
}

void SkyBox::Update()
{
}

GLuint SkyBox::getTextureId() {
	return textureID;
}
