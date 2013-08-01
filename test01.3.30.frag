#version 330 core

in vec2 UV;
out vec3 color;
uniform sampler2D texSampler;

void main(){
    vec3 texCol = texture( texSampler, UV ).rgb;
    color = texCol * UV.r * UV.g;
    //color = texCol;
}
