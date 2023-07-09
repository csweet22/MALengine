#version 400

// Ouput data
out vec4 color;


in vec3 test;

void main(){
    color = vec4(test.r, 1.0, test.b, 1.0);
}
