#version 440

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	float intensity;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vev4 fs_color;

uniform Material material;
uniform PointLight pointlight;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

vec3 calculateAmbient(Material material)
{
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	float diffuse = clamp(dot(posToLightDirVec, normalize(vs_normal)), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;
	return diffuseFinal;
}


