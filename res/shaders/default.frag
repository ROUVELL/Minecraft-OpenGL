#version 460 core

layout (location = 0) out vec3 FragColor;

uniform sampler2D u_tex0;

in vec2 uv;
in vec3 voxelColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1.0 / gamma;

void main()
{
	vec4 color = texture(u_tex0, uv);
	color.rbg = pow(color.rbg, gamma);

	if (color.a < 0.1)
		color.rbg += voxelColor;

	color.rgb = pow(color.rgb, invGamma);
	FragColor = color.rbg;
}