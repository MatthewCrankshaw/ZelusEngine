#version 330 core

out vec4 FragColor;

in vec3 fragPos;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 colour;

uniform bool textured;

void main(){
    vec4 fragC;
    if(!textured){
        fragC = vec4(colour, 1.0);
    }else{
        fragC = texture(texture1, TexCoord);
    }

    FragColor = fragC;
}