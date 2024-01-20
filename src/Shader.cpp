#include "Shader.h"

#include <fstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"

static const std::string shaderDir{ "D:\\Code\\C++\\Minecraft OpenGL\\res\\shaders\\" };

static std::string loadShader(const std::string& shaderName)
{
    std::ifstream file(shaderDir + shaderName, std::ios::binary);
    if (file.is_open())
    {
        std::string content;
        file.seekg(0, std::ios::end);
        content.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&content[0], content.size());
        file.close();
        return std::move(content);
    }

    std::cerr << "SHADER_LOADER::ERROR: Can`t load shader: '" << shaderName << "'!";
    return std::string{};
}

Shader::Shader(const std::string& vShader, const std::string& fShader)
{
    Load(vShader, fShader);
}


Shader::Shader(const std::string& name)
{
    Load(name + ".vert", name + ".frag");
}

unsigned int Shader::GetUniformLoc(const char* name) const
{
    return glGetUniformLocation(ID, name);
}

void Shader::SetTexture(const Texture& texture, const char* uniform)
{
    glUniform1i(GetUniformLoc(uniform), texture.GetUnit());
}

void Shader::SetCamPos(const glm::vec3& vector)
{
    SetVec3("u_camPos", vector);
}

void Shader::SetCamMat(const glm::mat4 matrix)
{
    SetMat4("u_camMat", matrix);
}

void Shader::SetModelMat(const glm::mat4& model)
{
    SetMat4("u_modelMat", model);
}

void Shader::SetMat4(const char* uniform, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLoc(uniform), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec3(const char* uniform, const glm::vec3& vector)
{
    glUniform3f(GetUniformLoc(uniform), vector.x, vector.y, vector.z);
}

void Shader::SetVec3(const char* uniform, float x, float y, float z)
{
    glUniform3f(GetUniformLoc(uniform), x, y, z);
}

void Shader::Load(const std::string& name)
{
    Load(name + ".vert", name + ".frag");
}

void Shader::Load(const std::string& vShader, const std::string& fShader)
{
    const std::string vertShader = loadShader(vShader);
    const std::string fragShader = loadShader(fShader);
    const char* vertexShaderSource = vertShader.c_str();
    const char* fragmentShaderSource = fragShader.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX_SHADER");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "FRAGMENT_SHADER");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::CheckCompileErrors(unsigned int shader, const char* type)
{
    // Stores status of compilation
    GLint hasCompiled{ GL_TRUE };
    // Character array to store error message in
    char infoLog[1024];
    if (type == "PROGRAM")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
        if (hasCompiled == GL_FALSE)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
        }
        return;
    }

    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
    }
}
