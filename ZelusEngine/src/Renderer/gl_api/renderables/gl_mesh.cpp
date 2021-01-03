#include "gl_mesh.h"

long GLMesh::memoryVertexUsed = 0;
long GLMesh::memoryIndicesUsed = 0;

GLMesh::GLMesh(Ref<std::vector<Vertex>> vertices, Ref<std::vector<unsigned int>> indices, Ref<std::vector<Ref<Texture>>> textures) {
	this->vertices = vertices; 
	this->indices = indices; 
	this->textures = textures;

	this->verticesSize = vertices->size();
	this->indicesSize = indices->size();

	SetupMesh();

}

void GLMesh::Draw(const Ref<Camera> camera) {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::GEOMETRY_PASS);

	if (textures->size() >= 1) {
		shader->SetBool("textured", true);
	}
	else {
		shader->SetBool("textured", false);
	}

	for (unsigned int i = 0; i < textures->size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures->at(i)->GetTextureType();

		if (name == "texture_diffuse") {
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular") {
			number = std::to_string(specularNr++);
		}
		else if (name == "texture_normal") {
			number = std::to_string(normalNr++);
		}
		else if (name == "texture_height") {
			number = std::to_string(heightNr++);
		}

		shader->SetInt((name + number).c_str(), i);

		glBindTexture(GL_TEXTURE_2D, textures->at(i)->GetHandle());
	}

	glBindVertexArray(mVao); 
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0); 
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void GLMesh::Update() {

}

void GLMesh::SetupMesh() {

	glGenVertexArrays(1, &mVao); 
	glGenBuffers(1, &mVbo); 
	glGenBuffers(1, &mEbo); 

	glBindVertexArray(mVao); 

	glBindBuffer(GL_ARRAY_BUFFER, mVbo); 

	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(Vertex), &vertices->at(0), GL_STATIC_DRAW); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), &indices->at(0), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);

	memoryVertexUsed += vertices->size() * sizeof(Vertex);
	memoryIndicesUsed += vertices->size() * sizeof(int);

	gLog->AddLog("[info] size of vertices: %d", memoryVertexUsed);
	gLog->AddLog("[info] size of indices: %d", memoryIndicesUsed);

	vertices.reset();
	indices.reset();
	
}