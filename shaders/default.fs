#version 400

// Ouput data
out vec4 color;


in vec3 test;
in vec2 uvs_vs;
in float perlinNoise;
uniform float time;


void main(){
    color = vec4(uvs_vs.r, uvs_vs.g, (test.y * 2.0), 1.0);
    color = vec4(perlinNoise - 0.5, perlinNoise - 0.5, perlinNoise - 0.5 ,1.0);
    // color = vec4(0, 0, (test.y * 2.0), 1.0);
}
