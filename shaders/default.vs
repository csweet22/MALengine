#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvs;

out vec3 test;

out vec2 uvs_vs;

uniform mat4 MVP;

uniform float time;

void main(){
    uvs_vs = uvs;
    float y_offset = sin( (uvs_vs.x - 0.5) * (uvs_vs.y - 0.5) * 20.0 + time * 2.0) / 4.0;

    test = vertexPosition_modelspace;
    test.y = test.y + y_offset;
    gl_Position = MVP * vec4(vertexPosition_modelspace,1.0);
    gl_Position.y = gl_Position.y + y_offset;
}
