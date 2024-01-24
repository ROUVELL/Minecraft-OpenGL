#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in uint a_voxelId;
layout (location = 2) in uint a_faceId;

uniform mat4 u_camMat;
uniform mat4 u_modelMat;

out vec2 uv;
flat out uint voxelId;
flat out uint faceId;

const vec2 uvCoords[4] = vec2[4]
(
	vec2(1, 0), vec2(1, 1),
	vec2(0, 0), vec2(0, 1)
);

const int uvIndices[12] = int[12]
(
	1, 0, 2, 1, 2, 3,
	3, 0, 2, 3, 1, 0
);

void main()
{
	voxelId = a_voxelId;
	faceId = a_faceId;
	uv = uvCoords[uvIndices[gl_VertexID % 6 + (a_faceId & 1) * 6]];
	gl_Position = u_camMat * u_modelMat * vec4(a_pos, 1.0);
}