#version 120

attribute vec3 vertexPosition;
attribute vec2 vertexUV;
attribute vec3 normal;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightDir;

varying vec3 normalCam;
varying vec3 lightDirCam;
varying vec2 UV;

void main(){
    normalCam = ( V*M*vec4(normal,0.0) ).xyz;
    lightDirCam = ( V*vec4(-lightDir, 0.0) ).xyz;
    vec4 v = vec4( vertexPosition, 1 );
    gl_Position = MVP * v;
    UV = vertexUV;
}
