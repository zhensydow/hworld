#version 330 core

layout(location = 0) in vec3 vertexPosition;
uniform mat4 MVP;
out vec3 position;

void main(){
    vec4 v = vec4( vertexPosition, 1 );
    gl_Position = MVP * v;
    position = vertexPosition;
}
