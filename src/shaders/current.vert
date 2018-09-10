#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 objectColor;
out vec3 lightColor;
out vec3 normal;
out vec3 fragPos;

uniform vec3 uObjectColor;
uniform vec3 uLightColor;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
    objectColor = uObjectColor;
    lightColor = uLightColor;
    normal = aNormal;
    fragPos = vec3(uModel * vec4(aPos, 1.0));   // world position
}