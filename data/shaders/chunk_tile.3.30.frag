#version 330 core

in vec2 UV;
in vec3 normalCam;
in vec3 lightDirCam;
out vec3 color;
uniform sampler2D texSampler;

void main(){
    vec3 n = normalize( normalCam );
    vec3 l = normalize( lightDirCam );
    float cosTheta = clamp( dot(n, l), 0, 1 );
    vec3 texCol = texture( texSampler, UV ).rgb;
    //color = texCol;
    color = texCol * 0.3 + texCol * cosTheta * 0.7;
}
