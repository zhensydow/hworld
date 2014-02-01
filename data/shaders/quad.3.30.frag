#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float width;
uniform float height;

void main(){
    color = texture( renderedTexture, UV ).xyz ;
    vec2 dist = vec2( sin(width*UV.x), cos(height*UV.y) );
    //vec2 dist = vec2( sin(time+width*UV.x), cos(time+height*UV.y) );
    color = texture( renderedTexture, UV + 0.005*dist ).xyz ;
}

