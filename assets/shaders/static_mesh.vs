#version 330 core

in vec3 pos;
in vec2 uv;
in vec3 normal;

out vec2 uvFrag;
out vec3 normalFrag;

uniform mat4 gWvp;

void main() {
    gl_Position = gWvp * vec4(pos, 1.0) ;
    
    uvFrag = uv;
    normalFrag = normal;
}

