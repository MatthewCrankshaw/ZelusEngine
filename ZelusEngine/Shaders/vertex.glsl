#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec3 fragPos; 
out vec3 ourNormal; 
out vec2 TexCoord;
        
void main(){ 
    fragPos = vec3(model * vec4(aPos, 1.0));
    ourNormal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    gl_Position = projection * view * vec4(fragPos.x, fragPos.y, fragPos.z, 1.0);
}