#version 120

attribute vec3 vertexPosition;
attribute vec2 vertexUV;
uniform mat4 MVP;

varying vec2 UV;

void main(){
    vec4 v = vec4( vertexPosition, 1 );
    gl_Position = MVP * v;
    UV = vertexUV;
}
