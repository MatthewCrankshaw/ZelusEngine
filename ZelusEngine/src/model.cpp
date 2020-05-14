#include "model.h"

Model::Model(std::string const& path){
	LoadModel(path);
}


void Model::Draw(const Camera &camera) {
    glm::mat4 viewMatrix, projectionMatrix;
    camera.GetViewMatrix(viewMatrix);
    camera.GetProjectionMatrix(projectionMatrix);

    /*glm::vec3 lightPos = gUserInterface->GetLightPosition();
    glm::vec3 lightDir = gUserInterface->GetLightDirection();
    glm::vec3 lightAmbient = gUserInterface->GetLightAmbient();
    glm::vec3 lightDiffuse = gUserInterface->GetLightDiffuse();
    glm::vec3 lightSpecular = gUserInterface->GetLightSpecular();

    glm::vec3 materialAmbient = gUserInterface->GetMaterialAmbient();
    glm::vec3 materialDiffuse = gUserInterface->GetMaterialDiffuse();
    glm::vec3 materialSpecular = gUserInterface->GetMaterialSpecular();*/

    //Shader* shader = gShaderManager->getMultiLightShader();
    Shader* shader = gShaderManager->getGeometryPassShader();

    //shader->SetVec3("light.position", lightPos);
    //shader->SetVec3("light.direction", lightDir);
    //shader->SetVec3("light.ambient", lightAmbient);
    //shader->SetVec3("light.diffuse", lightDiffuse);
    //shader->SetVec3("light.specular", lightSpecular);
    //shader->SetFloat("light.constant", gUserInterface->GetLightConstant());
    //shader->SetFloat("light.linear", gUserInterface->GetLightLinear());
    //shader->SetFloat("light.quadratic", gUserInterface->GetLightQuadratic());
    //shader->SetFloat("light.cutOff", glm::cos(glm::radians(gUserInterface->GetLightInnerCutOff())));
    //shader->SetFloat("light.outerCutOff", glm::cos(glm::radians(gUserInterface->GetLightOuterCutOff())));

    //shader->SetFloat("material.shininess", gUserInterface->GetMaterialShininess());

    mModelMat = mRotation * mTranslation * mScale;

    shader->Use();
    shader->SetMat4("view", viewMatrix);
    shader->SetMat4("model", mModelMat);
    shader->SetMat4("projection", projectionMatrix);

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw();
	}

    shader->UnUse();
}

void Model::Update() {

}

void Model::LoadModel(std::string const& path) {
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "MODEL::LOADMODEL::ERROR: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/')); 

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* aimesh, const aiScene* scene) {
    std::vector<Vertex>* vertices = new std::vector<Vertex>();
    std::vector<unsigned int>* indices = new std::vector<unsigned int>();
    std::vector<Texture>* textures = new std::vector<Texture>();

    vertices->reserve(aimesh->mNumVertices);
    indices->reserve(aimesh->mNumFaces);

    std::cout << "Vertices: " << aimesh->mNumVertices << std::endl;
    std::cout << "Faces: " << aimesh->mNumFaces << std::endl;

    for (unsigned int i = 0; i < aimesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        // positions
        vector.x = aimesh->mVertices[i].x;
        vector.y = aimesh->mVertices[i].y;
        vector.z = aimesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (aimesh->mNormals) {
            vector.x = aimesh->mNormals[i].x;
            vector.y = aimesh->mNormals[i].y;
            vector.z = aimesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        else {
            vector.x = 0;
            vector.y = 0;
            vector.z = 1;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (aimesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = aimesh->mTextureCoords[0][i].x;
            vec.y = aimesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        if (aimesh->mTangents) {
            // tangent
            vector.x = aimesh->mTangents[i].x;
            vector.y = aimesh->mTangents[i].y;
            vector.z = aimesh->mTangents[i].z;
            vertex.Tangent = vector;
        }
        else {
            vector.x = 0;
            vector.y = 0;
            vector.z = 0;
            vertex.Tangent = vector;
        }

        if (aimesh->mBitangents) {
            // bitangent
            vector.x = aimesh->mBitangents[i].x;
            vector.y = aimesh->mBitangents[i].y;
            vector.z = aimesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else {
            vector.x = 0;
            vector.y = 0;
            vector.z = 0;
            vertex.Bitangent = vector;
        }
        vertices->push_back(vertex);
    }

    for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
        aiFace face = aimesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices->push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];

    std::vector<Texture>* diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures->insert(textures->end(), diffuseMaps->begin(), diffuseMaps->end());

    std::vector<Texture>* specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures->insert(textures->end(), specularMaps->begin(), specularMaps->end());

    std::vector<Texture>* normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures->insert(textures->end(), normalMaps->begin(), normalMaps->end());

    std::vector<Texture>* heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures->insert(textures->end(), heightMaps->begin(), heightMaps->end());

    return Mesh(vertices, indices, textures);
}

std::vector<Texture>* Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture>* textures = new std::vector<Texture>();

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;

        mat->GetTexture(type, i, &str);

        bool skip = false;

        for (unsigned int j = 0; j < texturesLoaded.size(); j++) {
            if (std::strcmp(texturesLoaded[j].GetFilename().data(), str.C_Str()) == 0) {
                textures->push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture texture;
            texture.LoadRegularTexture(directory + "/", str.C_Str(), false);
            texture.SetTextureType(typeName);
            textures->push_back(texture);
            texturesLoaded.push_back(texture);
        }
    }
    return textures;
}