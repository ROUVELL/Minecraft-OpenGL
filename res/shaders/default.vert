#version 330 core

layout (location = 0) in uint a_vertData;

uniform mat4 u_camMat;
uniform mat4 u_modelMat;

out vec2 UV;
out vec3 voxelColor;

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

int x, y, z;
int voxelId;
vec2 uv;

void unpackData()
{
	// return (x << 23) | (y << 16) | (z << 10) | (voxelId << 2)  | uv;

	x = int(a_vertData >> 23u);
	y = int((a_vertData >> 16u) & 127u);
	z = int((a_vertData >> 10u) & 63u);

	voxelId = int((a_vertData >> 2u) & 255u);
	uv = vec2((a_vertData >> 1u) & 1u, a_vertData & 1u);
	
}
//
//int mt_rng(int seed) {
//    const int a = 0x9908B0DF;
//    const int b = 0x9D2C5680;
//    const int c = 0xEFC60000;
//    const int d = 0xFFFFFFFF;
//
//    seed ^= (seed >> 30);
//    seed ^= (seed << 11);
//    seed ^= (seed >> 21);
//
//    return (seed * a) ^ ((seed ^ d) & b) ^ ((seed & d) << c);
//}
//
//float random(inout int seed)
//{
//	seed += 1;
//    return float(mt_rng(seed)) / float(0xFFFFFFFFu);
//}
//
//vec3 randomColor()
//{
//	int seed = voxelId;
//	return vec3(random(seed), random(seed), random(seed));
//}
//
vec3 hash31(float p)
{
	vec3 p3 = fract(vec3(p + 21.2) * vec3(0.1031, 0.1030, 0.973));
	p3 += dot(p3, p3.yzx + 33.33);
	return fract((p3.xxy, p3.yzz) * p3.zyx) + 0.05;
}

void main()
{
	unpackData();

	voxelColor = hash31(voxelId);
	UV = uv;

	gl_Position = u_camMat * u_modelMat * vec4(x, y, z, 1.0);
}