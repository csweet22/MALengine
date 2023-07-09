#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

out vec3 test;

uniform mat4 MVP;

void main(){
    test = vertexPosition_modelspace;
    gl_Position = MVP * vec4(vertexPosition_modelspace,1.0);
}
