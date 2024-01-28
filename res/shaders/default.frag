#version 330 core

layout (location = 0) out vec3 FragColor;

uniform sampler2D u_tex0;

in vec2 uv;
in vec3 voxelColor;
in float ao;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1.0 / gamma;

void main()
{
	vec3 color = texture(u_tex0, uv).rgb;
	color = pow(color, gamma);

	color *= voxelColor;
	//color = color * 0.001 + vec3(1);
	color *= ao;

	color = pow(color, invGamma);
	FragColor = color;
}