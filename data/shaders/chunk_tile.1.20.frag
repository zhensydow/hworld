#version 120

varying vec2 UV;
uniform sampler2D texSampler;

void main(){
    vec3 texCol = texture2D( texSampler, UV ).rgb;
    gl_FragColor = vec4( texCol.rgb, 1.0 );
}
