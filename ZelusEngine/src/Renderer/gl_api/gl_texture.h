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

	void CreateEmptyTexture(int width, int height, int format) override;
	void LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip) override;
	void LoadCubeMapTexture(std::string textureDirectory, std::vector<std::string> faceTextureFilenames, bool flip) override;

private:
	unsigned char* mData;
};

