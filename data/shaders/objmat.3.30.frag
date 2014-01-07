#version 330 core

uniform vec3 diffuse;

in vec3 position;
out vec3 color;

void main(){
    vec3 steps = floor( mod( position, 2 ) );
    float a = floor( mod(steps.x + steps.y + steps.z, 2) );
    color = mix( diffuse, vec3( 0, 0.9, 0 ), a );
}
