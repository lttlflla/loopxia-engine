#version 420 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in ivec4 boneIDs;
layout(location = 4) in vec4 boneWeights;

out vec2 uvFrag;
out vec3 normalFrag;

const int MAX_BONES = 200;

uniform mat4 gWvp;
uniform mat4 gBones[MAX_BONES];

void main() {
    mat4 boneTransform = gBones[boneIDs[0]] * boneWeights[0];
    boneTransform     += gBones[boneIDs[1]] * boneWeights[1];
    boneTransform     += gBones[boneIDs[2]] * boneWeights[2];
    boneTransform     += gBones[boneIDs[3]] * boneWeights[3];

    vec4 posT = boneTransform * vec4(pos, 1.0);
    gl_Position = gWvp * posT;
    //gl_Position = gWvp * vec4(pos, 1.0) ;
    
    uvFrag = uv;
    normalFrag = normal;
}

