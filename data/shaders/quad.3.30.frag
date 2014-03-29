#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;
uniform float width;
uniform float height;

void main(){
    vec2 dist = vec2( sin(10.f*time+width*UV.x), cos(10.f*time+height*UV.y) );
    color = texture( renderedTexture, UV + 0.005*dist ).xyz ;
}

