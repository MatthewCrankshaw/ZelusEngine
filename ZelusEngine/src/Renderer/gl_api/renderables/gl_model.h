#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "gl_mesh.h"
#include "gl_renderable.h"
#include "../texture/gl_texture.h"
#include "../../../ref.h"
#include "../../../user_interface.h"
#include "../../../shader_manager.h"
#include "../../texture_factory/gl_texture_factory.h"

#include <string> 
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <future>

extern Ref<UserInterface> gUserInterface;
extern Ref<Log> gLog;
extern Ref<ShaderManager> gShaderManager;

class GLModel : public GLRenderable
{
public:
	GLTextureFactory texFactory;
	std::vector<Ref<Texture>> texturesLoaded;
	std::vector<Ref<GLMesh>> meshes;
	std::string directory;
	bool gammaCorrection;

	GLModel(std::string const& path);

	void Draw(const Ref<Camera> camera) override;
	void Update() override;

private:
	glm::mat4 mModelMat;

	void LoadModel(std::string const& path);

	void ProcessNode(aiNode* node, const aiScene* scene);

	void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	Ref<std::vector<Ref<Texture>>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};