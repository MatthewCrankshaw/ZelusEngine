#version 330 core

out vec4 FragColor;

struct Material {
    vec3 ambient; 
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};

in vec3 fragPos;
in vec3 ourNormal;
in vec2 TexCoord;

uniform sampler2D texture1;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main(){
    vec3 ambient = light.ambient * material.ambient;

    //diffuse
    vec3 norm = normalize(ourNormal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    //specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = (ambient + diffuse + specular) * vec3(texture(texture1, TexCoord));

    FragColor = vec4(result, 1.0);
}