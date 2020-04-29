#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 ourColour;


void main(){
    FragColor = vec4(ourColour, 1.0);
}