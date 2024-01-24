#version 460 core

layout (location = 0) out vec4 FragColor;

uniform sampler2DArray u_tex0_array;

in vec2 uv;
flat in uint voxelId;
flat in uint faceId;

//const vec3 gamma = vec3(2.2);
//const vec3 invGamma = 1.0 / gamma;

void main()
{
	vec2 face_uv = uv;
	face_uv.x = uv.x / 3.0 - min(faceId, 2) / 3.0;

	vec4 color = texture(u_tex0_array, vec3(face_uv, voxelId));
	//color.rbg = pow(color.rbg, gamma);

	//color.rgb = pow(color.rgb, invGamma);
	FragColor = color;
}