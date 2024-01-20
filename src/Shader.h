#pragma once

#include <string>

#include <glm/glm.hpp>

class Texture;

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& name);
	Shader(const std::string& vShader, const std::string& fShader);

	void SetTexture(const Texture& texture, const char* uniform);
	void SetCamPos(const glm::vec3& vector);
	void SetCamMat(const glm::mat4 matrix);
	void SetModelMat(const glm::mat4& model);
	void SetMat4(const char* uniform, const glm::mat4& matrix);
	void SetVec3(const char* uniform, const glm::vec3& vector);
	void SetVec3(const char* uniform, float x, float y, float z);

	void Load(const std::string& name);
	void Load(const std::string& vShader, const std::string& fShader);

	void Activate();
	void Delete();

private:
	unsigned int ID{ 0 };

	inline unsigned int GetUniformLoc(const char* name) const;

	void CheckCompileErrors(unsigned int shader, const char* type);
};