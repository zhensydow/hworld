#version 120

uniform vec3 diffuse;

varying vec3 normalCam;
varying vec3 lightDirCam;

void main(){
    vec3 n = normalize( normalCam );
    vec3 l = normalize( lightDirCam );
    float cosTheta = clamp( dot(n, l), 0, 1 );
    gl_FragData[0] = vec4( diffuse * 0.3 + diffuse * cosTheta * 0.7, 1.0 );
}
