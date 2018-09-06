#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 color;

uniform vec4 uColor;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
    color = uColor;
}