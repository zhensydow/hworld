#version 120

varying vec2 UV;

uniform sampler2D renderedTexture;
uniform float width;
uniform float height;

void main(){
    gl_FragColor = vec4( texture2D( renderedTexture, UV ).rgb, 1 ) ;
    vec2 dist = vec2( sin(width*UV.x), cos(height*UV.y) );
    //vec2 dist = vec2( sin(time+width*UV.x), cos(time+height*UV.y) );
    gl_FragColor = vec4( texture2D( renderedTexture, UV + 0.005*dist ).rgb, 1 ) ;
}

