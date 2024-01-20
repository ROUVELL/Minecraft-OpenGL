#include "Texture.h"

#include <string>

#include <glad/glad.h>
#include <stb/stb_image.h>

static const std::string TEXTURES_DIR{ "D:\\Code\\C++\\Minecraft OpenGL\\res\\textures\\" };

Texture::Texture(const char* name, unsigned int unit)
{
    Load(name, unit);
}

void Texture::Load(const char* name, unsigned int unit)
{
    this->unit = unit;

    const std::string imgPath = TEXTURES_DIR + name;

    glCreateTextures(GL_TEXTURE_2D, 1, &ID);

    glTexParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int imgW, imgH, imgChans;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* bytes = stbi_load(imgPath.c_str(), &imgW, &imgH, &imgChans, 0);

    glTextureStorage2D(ID, 1, GL_RGBA8, imgW, imgH);

    if (imgChans == 4)
        glTextureSubImage2D(ID, 0, 0, 0, imgW, imgH, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    else if (imgChans == 3)
        glTextureSubImage2D(ID, 0, 0, 0, imgW, imgH, GL_RGB, GL_UNSIGNED_BYTE, bytes);

    glGenerateTextureMipmap(ID);

    stbi_image_free(bytes);
}

void Texture::Bind() const
{
    glBindTextureUnit(unit, ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
    //glBindTextureUnit(type, 0);
}

void Texture::Delete() const
{
	glDeleteTextures(1, &ID);
}
