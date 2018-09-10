#version 330 core

in vec4 objectColor;
in vec4 lightColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(objectColor * lightColor);
}