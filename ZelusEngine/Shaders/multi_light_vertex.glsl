#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent; 
layout (location = 4) in vec3 aBitangent;

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

uniform PointLight light;
uniform vec3 viewPos;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec3 fragPos; 
out vec3 ourNormal; 
out vec2 TexCoord;
out vec3 TangentLightPos;
out vec3 TangentViewPos; 
out vec3 TangentFragPos;
        
void main(){ 
    fragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aTexCoord;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N); 

    vec3 B = cross(N, T);

    mat3 TBN = transpose(mat3(T, B, N));

    TangentLightPos = TBN * light.position;
    TangentViewPos = TBN * viewPos;
    TangentFragPos = TBN * fragPos;

    //ourNormal = mat3(transpose(inverse(model))) * aNormal;
    

    gl_Position = projection * view * model * vec4(fragPos.x, fragPos.y, fragPos.z, 1.0);
}