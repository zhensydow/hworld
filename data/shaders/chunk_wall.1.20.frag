#version 120

varying vec2 UV;
varying vec3 normalCam;
varying vec3 lightDirCam;
uniform sampler2D texSampler;

void main(){
    vec3 n = normalize( normalCam );
    vec3 l = normalize( lightDirCam );
    float cosTheta = clamp( dot(n, l), 0, 1 );
    vec3 texCol = texture2D( texSampler, UV ).rgb;
    //gl_FragColor = vec4( texCol, 1.0 );
    gl_FragColor = vec4( texCol * 0.3 + texCol * cosTheta * 0.7, 1.0 );
}
