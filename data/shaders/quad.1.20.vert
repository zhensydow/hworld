#version 120

attribute vec3 vertexPosition;

varying vec2 UV;

void main(){
    gl_Position = vec4( vertexPosition, 1 );
    UV = (vertexPosition.xy + vec2( 1, 1 )) / 2.0;
}
