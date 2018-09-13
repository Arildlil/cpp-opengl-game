#ifndef MATERIAL_H
#define MATERIAL_H

#include "gl_header.h"

namespace Core {
    class Material {
        public:
            Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
            virtual ~Material();
            bool operator==(const Material& other);
            bool operator!=(const Material& other);
            const glm::vec3& ambient() const;
            const glm::vec3& diffuse() const;
            const glm::vec3& specular() const;
            float shininess() const;
        private:
            long m_id;
            glm::vec3 m_ambient; 
            glm::vec3 m_diffuse; 
            glm::vec3 m_specular; 
            float m_shininess;
    };

    static long m_materialID {0};
};

#endif