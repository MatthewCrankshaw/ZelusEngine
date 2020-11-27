#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../log.h"

extern Log* gLog;

class Texture
{
public:

	Texture();

	void CreateEmptyTexture(int width, int height, GLenum type = GL_RGBA);
	void LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip);
	void LoadCubeMapTexture(std::string textureDirectory, std::vector<std::string> faceTextureFilenames, bool flip);

	GLuint GetHandle();

	inline std::string GetPath() {
		return mPath;
	}

	inline std::string GetFilename() {
		return mFilename;
	}

	inline void SetTextureType(std::string textureType) {
		mTextureType = textureType;
	}

	inline std::string GetTextureType() {
		return mTextureType;
	}
private:
	std::string mPath;
	std::string mFilename;
	GLuint mHandle;
	std::string mTextureType;

	int mWidth, mHeight, mNChannels;
	unsigned char* mData;
	GLenum mFormat;

	bool mIsLoaded; 
};

