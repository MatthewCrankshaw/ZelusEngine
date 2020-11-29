#pragma once

#include "gl_texture.h"
#include "stb/stb_image.h"

GLTexture::GLTexture(){
    mFormat = GL_RGBA;
    mWidth = 0;
    mHeight = 0;
    mHandle = 0;
    mIsLoaded = false;

    glGenTextures(1, &mHandle);
}

void GLTexture::CreateEmptyTexture()
{
    glBindTexture(GL_TEXTURE_2D, mHandle);
    glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    mIsLoaded = true;
}

void GLTexture::LoadTextureFromFile(bool flip)
{
    int nChannels;
    glBindTexture(GL_TEXTURE_2D, mHandle);
    stbi_set_flip_vertically_on_load(flip);
    unsigned char* data = stbi_load(mPath.c_str(), &mWidth, &mHeight, &nChannels, 0);

    if (data == nullptr) {
        gLog->AddLog("[error] GLTexture::LoaderRegularTexture() : Could not load texture! %s", mPath.c_str());
    }

    if (data) {
        if (nChannels == 1) {
            mFormat = GL_RED;
        }
        else if (nChannels == 3) {
            mFormat = GL_RGB;
        }
        else if (nChannels == 4) {
            mFormat = GL_RGBA;
        }
        else {
            gLog->AddLog("[error] GLTexture::LoaderRegularTexture() : Unknown image format!");
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glad_glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    gLog->AddLog("[info] GLTexture::LoadRegularTexture() : GLTexture Loaded [%s]", mPath.c_str());

    mIsLoaded = true;
}

void GLTexture::LoadCubeMap(std::string paths[6])
{
    int nChannels;
    glBindTexture(GL_TEXTURE_CUBE_MAP, mHandle);
    stbi_set_flip_vertically_on_load(false);

    for (GLuint i = 0; i < 6; i++) {

        unsigned char* data = stbi_load(paths[i].c_str(), &mWidth, &mHeight, &nChannels, 0);

        if (data == nullptr) {
            std::cout << "ERROR::TEXTURE::LOADER Could not load texture (" << paths[i] << ")" << std::endl;
            exit(1);
        }

        if (data) {
            if (nChannels == 1) {
                mFormat = GL_RED;
            }
            else if (nChannels == 3) {
                mFormat = GL_RGB;
            }
            else if (nChannels == 4) {
                mFormat = GL_RGBA;
            }
            else {
                std::cerr << "TEXTURE::READIMAGE: Unknown image format" << std::endl;
                exit(1);
            }

            glad_glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cerr << "Failed to load texture: " << std::endl;
            exit(1);
        }

        gLog->AddLog("[info] GLTexture::LoadCubeMapTexture() : Cube Map GLTexture Loaded [%s]", mPath.c_str());
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    mIsLoaded = true;
}