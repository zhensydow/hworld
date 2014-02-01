#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;

void main(){
    color = vec3( 0, 1, 1 );
    color = texture( renderedTexture, UV ).xyz ;
    //color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz ;
}

