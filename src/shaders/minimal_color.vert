#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 ourColor;

uniform vec4 uColor;

void main() {
    gl_Position = vec4(aPos, 1.0f);
    ourColor = uColor;
}