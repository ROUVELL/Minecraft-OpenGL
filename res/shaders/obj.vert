#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

uniform mat4 model;
uniform mat4 camMat;

out vec2 UV;
out vec3 Normal;
out vec3 Position;

void main()
{
	UV = aUV;
	Normal = normalize(mat3(inverse(transpose(model))) * aNormal);
	Position = vec3(model * vec4(aPos, 1.0));

	gl_Position = camMat * model * vec4(aPos, 1.0);
}