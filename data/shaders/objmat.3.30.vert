#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal;
uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

out vec3 normalCam;
out vec3 lightDirCam;

void main(){
    vec4 v = vec4( vertexPosition, 1 );
    normalCam = ( V*M*vec4(normal,0.0) ).xyz;
    vec3 positionCam = ( V*M*vec4(vertexPosition, 1.0) ).xyz;
    vec3 lightPos = vec3( 1.0f, 10.0f, 1.0f );
    lightDirCam = ( V*vec4(lightPos, 1.0) ).xyz - positionCam;

    gl_Position = MVP * v;
}
