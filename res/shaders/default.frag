#version 330 core

layout (location = 0) out vec3 FragColor;

uniform sampler2D u_tex0;

in vec2 UV;
in vec3 voxelColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1.0 / gamma;

void main()
{
	vec3 color = texture(u_tex0, UV).rgb;
	color = pow(color, gamma);

	color *= voxelColor;

	color = pow(color, invGamma);
	FragColor = color;
}