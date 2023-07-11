#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvs;

out vec3 test;

out vec2 uvs_vs;

uniform mat4 MVP;

void main(){
    uvs_vs = uvs;
    test = vertexPosition_modelspace;
    gl_Position = MVP * vec4(vertexPosition_modelspace,1.0);
}
