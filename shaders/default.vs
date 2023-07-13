#version 400

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 uvs;

out vec3 test;

out vec2 uvs_vs;
out float perlinNoise;

uniform mat4 MVP;

uniform float time;

float permute(const in float x) { return mod(((x * 34.0) + 1.0) * x, 289); }
vec2 permute(const in vec2 x) { return mod(((x * 34.0) + 1.0) * x, 289); }
vec3 permute(const in vec3 x) { return mod(((x * 34.0) + 1.0) * x, 289); }
vec4 permute(const in vec4 x) { return mod(((x * 34.0) + 1.0) * x, 289); }

vec2 fade(vec2 t) {return t*t*t*(t*(t*6.0-15.0)+10.0);}

float cnoise(vec2 P){
    vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
    vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
    Pi = mod(Pi, 289.0); // To avoid truncation effects in permutation
    vec4 ix = Pi.xzxz;
    vec4 iy = Pi.yyww;
    vec4 fx = Pf.xzxz;
    vec4 fy = Pf.yyww;
    vec4 i = permute(permute(ix) + iy);
    vec4 gx = 2.0 * fract(i * 0.0243902439) - 1.0; // 1/41 = 0.024...
    vec4 gy = abs(gx) - 0.5;
    vec4 tx = floor(gx + 0.5);
    gx = gx - tx;
    vec2 g00 = vec2(gx.x,gy.x);
    vec2 g10 = vec2(gx.y,gy.y);
    vec2 g01 = vec2(gx.z,gy.z);
    vec2 g11 = vec2(gx.w,gy.w);
    vec4 norm = 1.79284291400159 - 0.85373472095314 * 
        vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11));
    g00 *= norm.x;
    g01 *= norm.y;
    g10 *= norm.z;
    g11 *= norm.w;
    float n00 = dot(g00, vec2(fx.x, fy.x));
    float n10 = dot(g10, vec2(fx.y, fy.y));
    float n01 = dot(g01, vec2(fx.z, fy.z));
    float n11 = dot(g11, vec2(fx.w, fy.w));
    vec2 fade_xy = fade(Pf.xy);
    vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
    float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
    return 2.3 * n_xy;
}


void main(){
    uvs_vs = uvs;
    perlinNoise = (cnoise( vec2(uvs_vs.r * 4.0 + time, uvs_vs.g  * 4.0 + time) ) + 1.0) / 4.0;
    perlinNoise += (cnoise( vec2(uvs_vs.r * 7.0 - time * 0.3, uvs_vs.g  * 7.0 + time * 0.7) ) + 1.0) / 4.0;

    float y_offset = sin( (uvs_vs.x - 0.5) * (uvs_vs.y - 0.5) * 20.0 + time * 2.0) / 4.0;
    y_offset = perlinNoise;

    test = vertexPosition_modelspace;
    test.y = test.y + y_offset;
    gl_Position = MVP * vec4(vertexPosition_modelspace,1.0);
    gl_Position.y = gl_Position.y + y_offset;
}
