#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "user_interface.h"
#include "shader_manager.h"
#include "texture.h"
#include "mesh.h"
#include "renderable.h"

#include <string> 
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

extern UserInterfaceManager* gUserInterface;
extern ShaderManager* gShaderManager;

class Model : public Renderable
{
public:
	std::vector<Texture> texturesLoaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	Model(std::string const& path);

	void Draw(const Camera &camera);

	void Update();

private:

	std::vector<Texture> diffuseMaps; 
	std::vector<Texture> specularMaps; 
	std::vector<Texture> normalMaps; 
	std::vector<Texture> heightMaps; 

	void LoadModel(std::string const& path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};