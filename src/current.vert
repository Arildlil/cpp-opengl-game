#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 color;

uniform vec4 uColor;
uniform mat4 uTrans;

void main() {
    gl_Position = uTrans * vec4(aPos, 1.0f);
    color = uColor;
}