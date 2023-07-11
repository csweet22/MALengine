#version 400

// Ouput data
out vec4 color;


in vec3 test;
in vec2 uvs_vs;

void main(){
    color = vec4(uvs_vs.r, uvs_vs.g, 0.0, 1.0);
}
