#version 460 core

out vec4 color;

in vec3 vertexPos;
in vec3 vertexNormal;
in vec2 vertexUVs;

uniform vec3 lightPosition = {-10.f,0.f,10.f};
uniform vec3 lightColor = {1.,1.,1.};
uniform vec3 cameraPos;

uniform sampler2D baseColorTexture;

void main()
{
	float ambientFactor = 0.3;
	vec3 ambient = ambientFactor * lightColor;

	float diffuseFactor = 0.5;
	vec3 lightDir = normalize(lightPosition - vertexPos);
	float diff = max(dot(lightDir, vertexNormal),0);
	vec3 diffuse = diffuseFactor * diff * lightColor;

	float specularFactor = 0.8;
	vec3 reflectDir = reflect(-lightDir, vertexNormal);
	vec3 viewDir = normalize(cameraPos - vertexPos);
	float spec = pow(max(dot(viewDir,reflectDir),0), 64);
	vec3 specular = specularFactor * spec * lightColor;

	color = vec4((ambient + diffuse + specular) ,1.) * texture(baseColorTexture,vertexUVs );
}