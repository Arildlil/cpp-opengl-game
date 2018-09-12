#version 330 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 normal;
out vec3 fragPos;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
    normal = aNormal;
    fragPos = vec3(uModel * vec4(aPos, 1.0));   // world position
}