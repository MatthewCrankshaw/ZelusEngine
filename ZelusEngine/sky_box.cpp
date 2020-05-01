#include "sky_box.h"

SkyBox::SkyBox(std::vector<std::string> textureFacesFilenames)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	Texture texture;
	texture.LoadCubeMapTexture("res/", textureFacesFilenames, false);
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

	setPosition(position);
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
