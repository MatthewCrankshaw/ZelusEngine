#pragma once
#include <iostream>
#include <string>
#include <vector>


class Texture
{
protected:
	unsigned int mHandle;
	unsigned int mFormat;
	std::vector<std::string> mPaths;
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
		mPaths.push_back(path);
	}

	inline void SetFormat(int format) {
		mFormat = format;
	}

	inline unsigned int GetHandle() {
		if (!mIsLoaded) {
			std::cout << "TEXTURE::GET_HANDLE: Error getting texture handle: GLTexture object created but texture not loaded. Load texture first" << mPaths.front() << std::endl;
			exit(1);
		}
		return mHandle;
	}

	inline std::vector<std::string> GetPaths() {
		return mPaths;
	}

	inline std::string GetTextureType() {
		return mTextureType;
	}
};

