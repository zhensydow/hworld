#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
uniform mat4 MVP;

out vec2 UV;

void main(){
    vec4 v = vec4( vertexPosition, 1 );
    gl_Position = MVP * v;
    UV = vertexUV;
}
