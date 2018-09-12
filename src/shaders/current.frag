#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 pos;
};

uniform Material material;
uniform Light light;
uniform vec3 uViewPos;

in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;


void main() {
    // ambient
    
    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.pos - fragPos);     // light direction normalized
    float diffuse = max(dot(norm, lightDir), 0.0);      // light impact, angle
    
    // specular
    vec3 viewDir = normalize(uViewPos - fragPos);    
    vec3 reflectDir = reflect(-lightDir, normal);
    float specular = pow( max ( dot(viewDir, reflectDir), 0.0), material.shininess);

    // results
    vec3 ambientResult = light.ambient * material.ambient;
    vec3 diffuseResult = light.diffuse * (diffuse * material.diffuse);
    vec3 specularResult = light.specular * (specular * material.specular);

    vec3 result = (ambientResult + diffuseResult + specularResult);

    FragColor = vec4(result, 1.0);
}