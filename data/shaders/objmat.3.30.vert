#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 lightDir;

out vec3 normalCam;
out vec3 lightDirCam;

void main(){
    vec4 v = vec4( vertexPosition, 1 );
    normalCam = ( V*M*vec4(normal,0.0) ).xyz;
    lightDirCam = ( V*vec4(-lightDir, 0.0) ).xyz;

    gl_Position = MVP * v;
}
