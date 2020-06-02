
#type vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec3 fragPos; 
out vec3 ourColour;
        
void main(){ 

    ourColour = aColour;

    fragPos = vec3(model * vec4(aPos.x, aPos.y, aPos.z, 1.0));

    gl_Position =   vec4(-1.5, -1.5, 0.0, 1.0) + (projection * view * vec4(fragPos.x, fragPos.y, fragPos.z, 1.0));
}

#type fragment
#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 ourColour;


void main(){
    FragColor = vec4(ourColour, 1.0);
}