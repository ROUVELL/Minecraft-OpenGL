#version 460 core

layout (location = 0) out vec4 FragColor;

uniform sampler2D u_tex0;

in vec2 uv;
in vec3 voxelColor;

const vec3 gamma = vec3(2.2);
const vec3 invGamma = 1.0 / gamma;

void main()
{
	vec4 color = texture(u_tex0, uv);
	color.rgb = pow(color.rgb, gamma);

	if (color.a < 0.1)
		color.rgb += voxelColor;

	color.rgb = pow(color.rgb, invGamma);
	FragColor = color;
}