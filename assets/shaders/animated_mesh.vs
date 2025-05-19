#version 330 core

in vec3 pos;
in vec2 uv;
in vec3 normal;
//in ivec4 boneIDs;
//in vec4 boneWeights;

out vec2 uvFrag;
out vec3 normalFrag;

const int MAX_BONES = 200;

uniform mat4 gWvp;
//uniform mat4 gBones[MAX_BONES];

void main() {
    //mat4 boneTransform = gBones[boneIDs[0]] * boneWeights[0];
    //oneTransform     += gBones[boneIDs[1]] * boneWeights[1];
    //boneTransform     += gBones[boneIDs[2]] * boneWeights[2];
    //oneTransform     += gBones[boneIDs[3]] * boneWeights[3];

    //vec4 posT = boneTransform * vec4(apos, 1.0);
    //gl_Position = gWvp * posT;
    gl_Position = gWvp * vec4(pos, 1.0) ;
    
    uvFrag = uv;
    normalFrag = normal;
}

