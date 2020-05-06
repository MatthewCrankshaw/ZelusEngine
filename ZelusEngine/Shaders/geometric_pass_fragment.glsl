#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpecular;

in vec2 TexCoords; 
in vec3 FragPos; 
in vec3 Normal;

uniform sampler2D texture_diffuse1; 
uniform sampler2D texture_specular1; 
uniform sampler2D texture_normal1;

uniform bool textureProvided;

void main()
{
	gPosition = FragPos;

	gNormal = normalize(Normal);
	//gNormal = normalize(texture(texture_normal1, TexCoords).rgb * 2.0 - 1.0);

	if(textureProvided){
		gAlbedoSpecular.rgb = texture(texture_diffuse1, TexCoords).rgb;
		gAlbedoSpecular.a = texture(texture_specular1, TexCoords).r;
	}else{
		gAlbedoSpecular.rgb = vec3(0.2, 0.2, 0.2);
		gAlbedoSpecular.a = 0.2;
	}
}