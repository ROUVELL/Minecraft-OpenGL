#pragma once

class Texture
{
public:
	Texture() = default;
	Texture(const char* name, unsigned int type, unsigned int unit = 0);

	unsigned int GetUnit() const { return unit; }

	void Load(const char* name, unsigned int type, unsigned int unit = 0);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

private:
	unsigned int ID{ 0 };
	unsigned int type{ 0 };
	unsigned int unit{ 0 };
};

