#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec3 ourColor;

uniform sampler2D texture1;
uniform vec3 lightColour;

void main(){
    FragColor = vec4(lightColour, 1.0);
}