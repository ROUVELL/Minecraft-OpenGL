#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uv;

uniform mat4 u_camMat;

out vec2 uv;

void main()
{
	uv = a_uv;
	gl_Position = u_camMat * vec4(a_pos, 1.0);
}