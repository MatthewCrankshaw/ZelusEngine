#pragma once
#include <string>

#include "../gl_api/texture/gl_texture.h"
#include "abstract_texture_factory.h"

class GLTextureFactory : public AbstractTextureFactory
{
public:
	Ref<Texture> CreateEmptyTexture(int width, int height, int format) override;
	Ref<Texture> LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip) override;
	Ref<Texture> LoadCubeMapTexture(std::string textureDirectory, std::string* faceTextureFilenames, bool flip) override;
};

