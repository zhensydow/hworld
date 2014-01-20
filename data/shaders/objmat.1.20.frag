#version 120

uniform vec3 diffuse;

varying vec3 normalCam;
varying vec3 lightDirCam;

void main(){
    vec3 n = normalize( normalCam );
    vec3 l = normalize( lightDirCam );
    float cosTheta = clamp( dot(n, l), 0, 1 );
    //gl_FragColor = vec4( diffuse, 1.0 );
    gl_FragColor.rgb = diffuse * 0.3 + diffuse * cosTheta * 0.7;
    gl_FragColor.a = 1.0;
}
