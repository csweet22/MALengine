#version 400

// Interpolated values from the vertex shaders
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec2 uv;

// Ouput data
out vec4 color;

uniform vec4 modelcolor;
uniform float alpha;
uniform sampler2D tex;

void main(){
    vec4 diffuse = texture(tex, uv);
    color = vec4(1.0, 1.0, 1.0, 1.0);
}
