#version 120

attribute vec3 vertexPosition;
attribute vec3 normal;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightDir;

varying vec3 normalCam;
varying vec3 lightDirCam;

void main(){
    vec4 v = vec4( vertexPosition, 1 );
    normalCam = ( V*M*vec4(normal,0.0) ).xyz;
    lightDirCam = ( V*vec4(-lightDir, 0.0) ).xyz;

    gl_Position = MVP * v;
}
