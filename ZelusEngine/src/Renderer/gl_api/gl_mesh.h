#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "gl_renderable.h"
#include "../../shader_manager.h"
#include "../../texture.h"
#include "../../ref.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex {
    glm::vec3 Position;

    glm::vec3 Normal;

    glm::vec2 TexCoords;

    glm::vec3 Tangent;

    glm::vec3 Bitangent;
};

extern ShaderManager* gShaderManager;

class Mesh : public Renderable {
private:
    /*  Mesh Data  */
    Ref<std::vector<Vertex>> vertices;
    Ref<std::vector<unsigned int>> indices;
    Ref<std::vector<Texture>> textures;

    int indicesSize;
    int verticesSize;
    
    static long memoryVertexUsed;
    static long memoryIndicesUsed;

public:
    /*  Functions  */
    // constructor
    Mesh(Ref<std::vector<Vertex>> vertices, Ref< std::vector<unsigned int>> indices, Ref<std::vector<Texture>> textures);

    // render the mesh
    void Draw(const Ref<Camera> camera) override;
    void Update() override;

    void SetupMesh();
};