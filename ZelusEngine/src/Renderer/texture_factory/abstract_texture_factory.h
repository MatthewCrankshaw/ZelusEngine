#pragma once
#include <string>

#include "../texture.h"
#include "../../ref.h"

class AbstractTextureFactory
{
	virtual Ref<Texture> CreateEmptyTexture(int width, int height, int format) = 0;
	virtual Ref<Texture> LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip) = 0;
	virtual Ref<Texture> LoadCubeMapTexture(std::string textureDirectory, std::string* faceTextureFilenames, bool flip) = 0;
};

