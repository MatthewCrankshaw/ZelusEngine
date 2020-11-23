#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../ref.h"
#include "../../user_interface.h"
#include "../../shader_manager.h"
#include "../../texture.h"
#include "gl_mesh.h"
#include "gl_renderable.h"

#include <string> 
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <future>

extern UserInterface* gUserInterface;
extern Log* gLog;
extern ShaderManager* gShaderManager;

class Model : public Renderable
{
public:
	std::vector<Texture> texturesLoaded;
	std::vector<Ref<Mesh>> meshes;
	std::string directory;
	bool gammaCorrection;

	Model(std::string const& path);

	void Draw(const Ref<Camera> camera) override;
	void Update() override;

private:
	glm::mat4 mModelMat;

	void LoadModel(std::string const& path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Ref<std::vector<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};