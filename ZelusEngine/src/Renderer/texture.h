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
	int mWidth, mHeight, mNChannels;
	bool mIsLoaded;
public:
	virtual void CreateEmptyTexture(int width, int height, int format) = 0;
	virtual void LoadRegularTexture(std::string textureDirectory, std::string textureFilename, bool flip) = 0;
	virtual void LoadCubeMapTexture(std::string textureDirectory, std::vector<std::string> faceTextureFilenames, bool flip) = 0;

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

	inline void SetTextureType(std::string textureType) {
		mTextureType = textureType;
	}
};

