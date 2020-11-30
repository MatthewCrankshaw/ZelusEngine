#include "gl_texture_factory.h"

Ref<Texture> GLTextureFactory::CreateEmptyTexture(int width, int height, int format)
{
	Ref<Texture> texture(new GLTexture());
	texture->SetTextureSize(width, height);
	texture->SetFormat(format);
	texture->CreateEmptyTexture();
	return texture;
}

Ref<Texture> GLTextureFactory::LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip)
{
	std::string path = textureDirectory + textureFilename;
	path = path.substr(0, path.find(" ", 0));

	Ref<Texture> texture(new GLTexture());
	texture->SetPath(path);
	texture->LoadTextureFromFile(flip);
	return texture;
}

Ref<Texture> GLTextureFactory::LoadCubeMapTexture(std::string textureDirectory, std::string* faceTextureFilenames, bool flip)
{
	std::string paths[6];
	for (int i = 0; i < 6; i++) {
		paths[i] = textureDirectory + faceTextureFilenames[i];
	}
	Ref<Texture> texture(new GLTexture());
	texture->LoadCubeMap(paths);
	return texture;
}
