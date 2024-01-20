#version 460 core

out vec4 FragColor;

uniform sampler2D tex_0;
uniform sampler2D tex_0_spec;

//uniform vec3 lightPos;
uniform vec3 camPos;

in vec2 UV;
in vec3 Normal;
in vec3 Position;

const float ambient = 0.2;
const vec3 lightPos = vec3(0.0, 0.4, -1.0);

float calculateSpecular(vec3 lightVec)
{
	vec3 viewDir = normalize(camPos - Position);
	vec3 reflectDir = reflect(-lightVec, Normal);
	return pow(max(dot(viewDir, reflectDir), 0.0), 16) * 0.5;
}

float calculateBlinnPhong(vec3 lightVec, float diffuse)
{
	if (diffuse != 0.0)
	{
		vec3 viewDir = normalize(camPos - Position);
		vec3 reflectDir = reflect(-lightVec, Normal);
		vec3 halfWayVec = normalize(viewDir + lightVec);
		return pow(max(dot(Normal, halfWayVec), 0.0), 16) * 0.5;
	}
	return 0.0;
}

void GetPointLight(inout vec4 color)
{
	vec3 lightVec = normalize(lightPos - Position);

	float dist = length(lightPos - Position);
	float a = 0.05;
	float b = 0.01;
	float inten = 1.0 / (a * dist * dist + b * dist + 1.0);

	float diffuse = max(dot(Normal, lightVec), 0.0);
	float specular = calculateBlinnPhong(lightVec, diffuse);

	color = color * (diffuse * inten + ambient) + texture(tex_0_spec, UV).r * specular * inten;
}

void GetDirectLight(inout vec4 color)
{
	vec3 lightVec = normalize(lightPos);

	float diffuse = max(dot(Normal, lightVec), 0.0);
	float specular = calculateSpecular(lightVec);

	color = color * (diffuse + ambient) + texture(tex_0_spec, UV).r * specular;
}

void GetSpotLight(inout vec4 color)
{
	float outerCone = 0.9;
	float innerCone = 0.95;

	vec3 lightDir = normalize(lightPos - Position);

	float diffuse = max(dot(Normal, lightDir), 0.0);
	float specular = calculateBlinnPhong(lightDir, diffuse);

	float angle = dot(vec3(0.0, -1.0, 0.0), -lightDir);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

	color = color * (diffuse * inten + ambient) + vec4(texture(tex_0_spec, UV).rgb, 1.0) * specular * inten;
}

void main()
{
	vec4 color = texture(tex_0, UV);
	
	//GetSpotLight(color);
	//GetPointLight(color);
	//GetDirectLight(color);

	FragColor = color;
}