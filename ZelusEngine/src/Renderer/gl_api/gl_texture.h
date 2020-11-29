#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../texture.h"
#include "../../log.h"

extern Log* gLog;

class GLTexture : public Texture
{
public:
	GLTexture();

	void CreateEmptyTexture() override;
	void LoadTextureFromFile(bool flip = false) override;
	void LoadCubeMap(std::string paths[6]) override;
};

