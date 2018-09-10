#version 330 core

in vec3 objectColor;
in vec3 lightColor;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 uLightPos;

void main() {
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;    // final ambient strength
    vec3 ambientResult = ambient * objectColor;     // final ambient effect

    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(uLightPos - fragPos); // light direction normalized
    float diff = max(dot(norm, lightDir), 0.0);     // light impact, angle
    vec3 diffuseResult = diff * lightColor;         // final diffuse effect

    vec3 result = (ambientResult + diffuseResult) * objectColor;

    FragColor = vec4(result, 1.0);
}