#include "Texture.h"

#include <string>

#include <glad/glad.h>
#include <stb/stb_image.h>

static const std::string TEXTURES_DIR{ "D:\\Code\\C++\\Minecraft OpenGL\\res\\textures\\" };

Texture::Texture(const char* name, unsigned int type, unsigned int unit)
{
    Load(name, unit);
}

void Texture::Load(const char* name, unsigned int type, unsigned int unit)
{
    this->unit = unit;
    this->type = type;

    const std::string imgPath = TEXTURES_DIR + name;

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int imgW, imgH, imgChans;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* bytes = stbi_load(imgPath.c_str(), &imgW, &imgH, &imgChans, 0);

    if (imgChans == 4)
        glTexImage2D(type, 0, GL_RGBA, imgW, imgH, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    else if (imgChans == 3)
        glTexImage2D(type, 0, GL_RGBA, imgW, imgH, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

    glGenerateMipmap(type);
    glBindTexture(type, 0);

    stbi_image_free(bytes);
}

void Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}

void Texture::Unbind() const
{
	glBindTexture(type, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &ID);
}
