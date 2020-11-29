#pragma once
#include <string>

#include "../gl_api/gl_texture.h"
#include "../../ref.h"

class GLTextureFactory
{
public:
	Ref<GLTexture> CreateEmptyTexture(int width, int height, int format);
	Ref<GLTexture> LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip);
	Ref<GLTexture> LoadCubeMapTexture(std::string textureDirectory, std::string* faceTextureFilenames, bool flip);
};

