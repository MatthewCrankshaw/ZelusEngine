#pragma once
#include <iostream>
#include <string>
#include <vector>


class Texture
{
protected:
	unsigned int mHandle;
	unsigned int mFormat;
	std::string mPath;
	std::string mFilename;
	std::string mTextureType;
	int mWidth, mHeight;
	bool mIsLoaded;
public:
	virtual void CreateEmptyTexture() = 0;
	virtual void LoadTextureFromFile(bool flip = false) = 0;
	virtual void LoadCubeMap(std::string paths[6]) = 0;

	inline void SetTextureSize(int width, int height) {
		mWidth = width;
		mHeight = height;
	}

	inline void SetTextureType(std::string textureType) {
		mTextureType = textureType;
	}

	inline void SetPath(std::string path) {
		mPath = path;
	}

	inline void SetFormat(int format) {
		mFormat = format;
	}

	inline unsigned int GetHandle() {
		if (!mIsLoaded) {
			std::cout << "TEXTURE::GET_HANDLE: Error getting texture handle: GLTexture object created but texture not loaded. Load texture first" << mPath << std::endl;
			exit(1);
		}
		return mHandle;
	}

	inline std::string GetPath() {
		return mPath;
	}

	inline std::string GetFilename() {
		return mFilename;
	}

	inline std::string GetTextureType() {
		return mTextureType;
	}
};

