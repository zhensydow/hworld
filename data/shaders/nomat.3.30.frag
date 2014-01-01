#version 330 core

in vec3 position;
out vec3 color;

void main(){
    vec3 steps = floor( mod( position, 2 ) );
    float a = floor( mod(steps.x + steps.y + steps.z, 2) );
    color = mix( vec3( 0.8, 0, 0.8 ), vec3( 0, 0.9, 0 ), a );
}
