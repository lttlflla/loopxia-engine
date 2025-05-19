#version 330 core

in vec2 uvFrag;
in vec3 normalFrag;

out vec4 FragColor;
uniform sampler2D textureSampler;

void main() {
    FragColor =  texture(textureSampler, uvFrag);
}
