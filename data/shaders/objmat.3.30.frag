#version 330 core

uniform vec3 diffuse;

in vec3 normalCam;
in vec3 lightDirCam;

layout(location = 0) out vec3 color;

void main(){
    vec3 n = normalize( normalCam );
    vec3 l = normalize( lightDirCam );
    float cosTheta = clamp( dot(n, l), 0, 1 );

    //color = diffuse
    color = diffuse * 0.3 + diffuse * cosTheta * 0.7;
}
