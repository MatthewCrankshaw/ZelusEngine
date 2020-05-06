#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Texture
{
public:

	Texture();

	void InitialiseTexture();
	void LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip);
	void LoadCubeMapTexture(std::string textureDirectory, std::vector<std::string> faceTextureFilenames, bool flip);

	GLuint GetHandle();

	std::string GetPath() {
		return path;
	}

	std::string GetFilename() {
		return filename;
	}

	void SetTextureType(std::string textureType) {
		this->textureType = textureType;
	}

	std::string GetTextureType() {
		return textureType;
	}
private:
	std::string path;
	std::string filename;
	GLuint handle;
	std::string textureType;

	int width, height, nChannels;
	unsigned char* data;
	GLenum format;

	//Check for if the texture is actually loaded or the texture object has just been created
	bool isLoaded; 
	bool isInitialised;
};

