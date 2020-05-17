#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader_manager.h"
#include "../texture.h"

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

class Mesh{
private:
    /*  Mesh Data  */
    std::vector<Vertex>* vertices;
    std::vector<unsigned int>* indices;
    std::vector<Texture>* textures;

    GLuint VAO; 
    GLuint VBO; 
    GLuint EBO;
    
public:
    /*  Functions  */
    // constructor
    Mesh(std::vector<Vertex>* vertices, std::vector<unsigned int>* indices, std::vector<Texture>* textures);

    // render the mesh
    void Draw();

    void Update();

    void SetupMesh();
};