#version 330 core

out vec4 FragColor;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight {
    vec3 position;

    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear; 
    float quadratic;

    vec3 ambient;
    vec3 diffuse; 
    vec3 specular;
};

struct SpotLight {
    vec3 position; 
    vec3 direction;
    float cutOff; 
    float outerCutOff; 

    float constant; 
    float linear; 
    float quadratic; 

    vec3 ambient; 
    vec3 diffuse; 
    vec3 specular;
};

in vec3 fragPos;
in vec3 ourNormal;
in vec2 TexCoord;
in vec3 TangentLightPos;
in vec3 TangentViewPos; 
in vec3 TangentFragPos;

uniform Material material;
uniform PointLight light;

uniform vec3 viewPos;
uniform bool textureProvided;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

vec3 calcDirLight(DirLight l, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight l, vec3 normal, vec3 viewDir);
vec3 calcSpotLight(SpotLight l, vec3 normal, vec3 viewDir);

void main(){

    //vec3 norm = normalize(ourNormal);
    vec3 norm = texture(texture_normal1, TexCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);

    //vec3 viewDir = normalize(viewPos - fragPos);
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);

    vec3 result = calcPointLight(light, norm, viewDir);

    vec3 color = pow(result, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0);
}

vec3 calcDirLight(DirLight l, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(l.position - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    vec3 ambient, diffuse, specular;
    if(textureProvided){
        ambient = l.ambient * texture(texture_diffuse1, TexCoord).rgb;
        diffuse = l.diffuse * diff * texture(texture_diffuse1, TexCoord).rgb;
        specular = l.specular * spec * texture(texture_specular1, TexCoord).rgb;
    }else{
        ambient = l.ambient;
        diffuse = l.diffuse * diff;
        specular = l.specular * spec;
    }

    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight l, vec3 normal, vec3 viewDir){
    
    //vec3 lightDir = normalize(l.position - fragPos);
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    //float diff = max(dot(normal, lightDir), 0.0);
    float diff = max(dot(lightDir, normal), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
    float dist = length(l.position - fragPos);
    float attenuation = 1.0 / (l.constant + l.linear * dist + l.quadratic * (dist * dist));

    vec3 color = texture(texture_diffuse1, TexCoord).rgb;

    vec3 ambient, diffuse, specular;

    if(textureProvided){
        ambient = l.ambient * color;
        diffuse = l.diffuse * color;
        specular = l.specular * spec * texture(texture_specular1, TexCoord).rgb;
    }else{
        ambient = l.ambient;
        diffuse = l.diffuse * diff;
        specular = l.specular * spec;
    }

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight l, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(l.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    float dist = length(l.position - fragPos);
    float attenuation = 1.0 / (l.constant + l.linear * dist + l.quadratic * (dist * dist));

    float theta = dot(lightDir, normalize(-l.direction)); 
    float epsilon = l.cutOff - l.outerCutOff;
    float intensity = clamp((theta - l.outerCutOff) / epsilon, 0.0, 1.0);

     vec3 ambient, diffuse, specular;

    if(textureProvided){
        ambient = l.ambient * texture(texture_diffuse1, TexCoord).rgb;
        diffuse = l.diffuse * diff * texture(texture_diffuse1, TexCoord).rgb;
        specular = l.specular * spec * texture(texture_specular1, TexCoord).rgb;
    }else{
        ambient = l.ambient;
        diffuse = l.diffuse * diff;
        specular = l.specular * spec;
    }

    ambient *= attenuation;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}