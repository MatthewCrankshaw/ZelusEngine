#include "gl_sky_box.h"

/**
 * \brief Creates a renderable cubemap
 * 
 * \param textureFacesFilenames A vector of all of the cubemap texture files in the order right, left, top, bottom, front, back
 */
GLSkyBox::GLSkyBox()
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
}

void GLSkyBox::Draw(const Ref<Camera> camera)
{
	glDepthFunc(GL_LEQUAL); 

	glBindVertexArray(mVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glDepthFunc(GL_LESS);
}

void GLSkyBox::Update()
{
}
