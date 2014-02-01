#version 120

varying vec2 UV;

uniform sampler2D renderedTexture;
uniform float time;
uniform float width;
uniform float height;

void main(){
    vec2 dist = vec2( sin(10.f*time+width*UV.x), cos(10.f*time+height*UV.y) );
    gl_FragColor = vec4( texture2D( renderedTexture, UV + 0.005*dist ).rgb, 1 ) ;
}

