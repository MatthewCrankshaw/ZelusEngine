#include "texture.h"

#include "stb/stb_image.h"

Texture::Texture(){
    mFormat = GL_RGBA;
    mWidth = 0;
    mHeight = 0;
    mNChannels = 4;
    mData = NULL;
    mHandle = 0;
    mIsLoaded = false;
}

void Texture::CreateEmptyTexture(int width, int height, GLenum type)
{
    mIsLoaded = true;
    glGenTextures(1, &mHandle);
    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadRegularTexture(std::string directory, std::string filename, bool flip)
{
    mFilename = filename;
    mPath = directory + filename;
    mPath = mPath.substr(0, mPath.find(" ", 0));
    
    glGenTextures(1, &mHandle);
    glBindTexture(GL_TEXTURE_2D, mHandle);

    stbi_set_flip_vertically_on_load(flip);
    mData = stbi_load(mPath.c_str(), &mWidth, &mHeight, &mNChannels, 0);

    if (mData == nullptr) {
        gLog->AddLog("[error] Texture::LoaderRegularTexture() : Could not load texture! %s", mPath.c_str());
    }

    if (mData) {
        if (mNChannels == 1) {
            mFormat = GL_RED;
        }
        else if (mNChannels == 3) {
            mFormat = GL_RGB;
        }
        else if (mNChannels == 4) {
            mFormat = GL_RGBA;
        }
        else {
            gLog->AddLog("[error] Texture::LoaderRegularTexture() : Unknown image format!");
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glad_glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, mData);
    stbi_image_free(mData);
    glGenerateMipmap(GL_TEXTURE_2D);

    gLog->AddLog("[info] Texture::LoadRegularTexture() : Texture Loaded [%s]", mPath.c_str());

    mIsLoaded = true;
}

void Texture::LoadCubeMapTexture(std::string textureDirectory, std::vector<std::string> faceTextureFilenames, bool flip) {
    mPath = textureDirectory + faceTextureFilenames[0];

    if (faceTextureFilenames.size() != 6) {
        gLog->AddLog("[error] Texture::LoadCubeMapTexture : Cube map must have 6 texture faces. %d were found.", faceTextureFilenames.size());
    }

    glGenTextures(1, &mHandle);
    glBindTexture(GL_TEXTURE_CUBE_MAP, mHandle);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(flip);

    for (GLuint i = 0; i < faceTextureFilenames.size(); i++) {

        unsigned char* data = stbi_load((textureDirectory + faceTextureFilenames[i]).c_str(), &width, &height, &nChannels, 0);

        if (data == nullptr) {
            std::cout << "ERROR::TEXTURE::LOADER Could not load texture (" << mPath << ")" << std::endl;
            exit(1);
        }

        if (data) {
            GLenum format;
            if (nChannels == 1) {
                format = GL_RED;
            }
            else if (nChannels == 3) {
                format = GL_RGB;
            }
            else if (nChannels == 4) {
                format = GL_RGBA;
            }
            else {
                std::cerr << "TEXTURE::READIMAGE: Unknown image format" << std::endl;
                exit(1);
            }

            glad_glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            glGenerateMipmap(GL_TEXTURE_2D);
#ifndef DEBUG
            std::cout << "TEXTURE::LOAD_CUBE_MAP_TEXTURE: loaded texture:  " << textureDirectory + faceTextureFilenames[i] << std::endl;
#endif // !DEBUG
        }
        else {
            std::cerr << "Failed to load texture: " << std::endl;
            exit(1);
        }

        gLog->AddLog("[info] Texture::LoadCubeMapTexture() : Cube Map Texture Loaded [%s]", mPath.c_str());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    mIsLoaded = true;
}

GLuint Texture::GetHandle()
{
    if (!mIsLoaded) {
        std::cout << "TEXTURE::GET_HANDLE: Error getting texture handle: Texture object created but texture not loaded. Load texture first" << mPath << std::endl;
        exit(1);
    }
    return mHandle;
}
