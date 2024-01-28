#version 330 core

layout (location = 0) in uint a_vertData;

uniform mat4 u_camMat;
uniform mat4 u_modelMat;

out vec2 uv;
out vec3 voxelColor;
out float ao;

const vec2 uvCoords[4] = vec2[4]
(
	vec2(0, 1), vec2(1, 1),
	vec2(0, 0), vec2(1, 0)
);

const int uvIndices[12] = int[12]
(
	1, 3, 2, 1, 2, 0,
	3, 2, 0, 3, 0, 1
);

const float faceShading[6] = float[6]
(
	1.0, 0.2,
	0.6, 0.6,
	0.6, 0.6
);

const float aoValues[4] = float[4]
(
	0.1, 0.35, 0.65, 1.0
);

int x, y, z;
int voxelId;
int faceId;
int aoId;
int flip;

void unpackData()
{
	// (x << 26) | (y << 19) | (z << 14) | (voxelId << 6) | (faceId << 3) | (ao << 1) | flip;

	x = int(a_vertData >> 26u);
	y = int((a_vertData >> 19u) & 127u);
	z = int((a_vertData >> 14u) & 31u);

	voxelId = int((a_vertData >> 6u) & 255u);
	faceId = int((a_vertData >> 3u) & 7u); 
	aoId = int((a_vertData >> 1u) & 3u);
	flip = int(a_vertData & 1u);
	
}
vec3 hash31()
{
	vec3 p3 = fract(vec3(voxelId * 21.2) * vec3(0.1031, 0.1030, 0.0973));
	p3 += dot(p3, p3.yzx + 33.33);
	return fract((p3.xxy + p3.yzz) * p3.zyx) + 0.05;
}

void main()
{
	unpackData();
	
	uv = uvCoords[uvIndices[gl_VertexID % 6 + (flip & 1) * 6]];
	voxelColor = hash31();
	ao = aoValues[aoId];

	gl_Position = u_camMat * u_modelMat * vec4(x, y, z, 1.0);
}