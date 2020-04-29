#include "texture.h"

#include "stb/stb_image.h"

Texture::Texture(){
    isLoaded = false;
}

void Texture::LoadRegularTexture(std::string directory, std::string filename, bool flip)
{
    this->filename = filename;
    this->path = directory + filename;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nChannels, 0);

    if (data == nullptr) {
        std::cout << "ERROR::TEXTURE::LOADER Could not load texture (" << path << ")" << std::endl;
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
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture: " << std::endl;
        exit(1);
    }

#ifndef DEBUG
    std::cout << "TEXTURE::LOAD_REGULAR_TEXTURE: loaded texture:  " << path << std::endl;
#endif // !DEBUG

    isLoaded = true;

    stbi_image_free(data);

}

void Texture::LoadCubeMapTexture(std::string textureDirectory, std::vector<std::string> faceTextureFilenames, bool flip) {
    this->path = textureDirectory + faceTextureFilenames[0];

    if (faceTextureFilenames.size() != 6) {
        std::cerr << "TEXTURE::LOAD_CUBE_MAP_TEXTURE: Cube map must have 6 texture faces, found: " << faceTextureFilenames.size() << " faces!" << std::endl;
        exit(1);
    }

    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(flip);

    for (GLuint i = 0; i < faceTextureFilenames.size(); i++) {

        unsigned char* data = stbi_load((textureDirectory + faceTextureFilenames[i]).c_str(), &width, &height, &nChannels, 0);

        if (data == nullptr) {
            std::cout << "ERROR::TEXTURE::LOADER Could not load texture (" << path << ")" << std::endl;
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
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    isLoaded = true;

}

GLuint Texture::GetHandle()
{
    if (isLoaded) {
        return handle;
    }
    else {
        std::cout << "TEXTURE::GET_HANDLE: Error getting texture handle: Texture object created but texture not loaded. Load texture first" << path << std::endl;
        exit(1);
    }
}
