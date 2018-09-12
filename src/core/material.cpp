#include "material.h"

using namespace Core;



Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    :m_ambient{ambient}, m_diffuse{diffuse}, m_specular{specular}, m_shininess{shininess}
{
    m_id = m_materialID++;
}

Material::~Material() {}

bool Material::operator==(const Material& other) {
    return ((*this).m_id == other.m_id);
}

bool Material::operator!=(const Material& other) {
    return !Material::operator==(other);
}

const glm::vec3& Material::ambient() const { 
    return m_ambient;     
}

const glm::vec3& Material::diffuse() const {
    return m_diffuse;
}

const glm::vec3& Material::specular() const {
    return m_specular;
}

const float Material::shininess() const {
    return m_shininess;
}